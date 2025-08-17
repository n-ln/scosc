// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCServerDetails.h"

#include "SlateOptMacros.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SButton.h"
#include "Styling/CoreStyle.h"
#include "SCOSCSettings.h"
#include "SCOSCServerManager.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "SSCOSCServerDetails"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSCOSCServerDetails::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBorder)
		.Padding(12.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 12.0f)
			[
				SAssignNew(TitleTextBlock, STextBlock)
				.Text(LOCTEXT("NoSelectionTitle", "No Selection"))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SAssignNew(ContentContainer, SVerticalBox)
			]
		]
	];

	BuildEmptyState();
}

void SSCOSCServerDetails::SetSelectedEndpoint(TSharedPtr<FSCOSCServerEndpointListItem> EndpointItem, bool bIsNewItem)
{
	CurrentEndpointItem = EndpointItem;
	CurrentAddressItem.Reset();

	if (EndpointItem.IsValid())
	{
		if (bIsNewItem)
		{
			// New endpoint
			OriginalServerName = EndpointItem->ServerName;
			OriginalServerConfig = EndpointItem->ServerConfig;

			if (TitleTextBlock.IsValid())
			{
				TitleTextBlock->SetText(LOCTEXT("NewEndpointTitle", "Create New OSC Server"));
			}
		
			BuildEndpointEditForm(true);
		}
		else
		{
			// Existing endpoint
			// Store original values for cancel functionality
			OriginalServerName = EndpointItem->ServerName;
			OriginalServerConfig = EndpointItem->ServerConfig;

			if (TitleTextBlock.IsValid())
			{
				TitleTextBlock->SetText(FText::Format(LOCTEXT("EndpointTitle", "OSC Server: {0}"), FText::FromName(EndpointItem->ServerName)));
			}
		
			BuildEndpointEditForm(false);
		}
	}
	else
	{
		BuildEmptyState();
	}
}

void SSCOSCServerDetails::SetSelectedAddress(TSharedPtr<FSCOSCServerAddressListItem> AddressItem)
{
	CurrentAddressItem = AddressItem;
	CurrentEndpointItem.Reset();

	if (AddressItem.IsValid())
	{
		if (TitleTextBlock.IsValid())
		{
			TitleTextBlock->SetText(FText::Format(LOCTEXT("AddressTitle", "OSC Address: {0}"), FText::FromString(AddressItem->OSCAddress)));
		}
		
		BuildAddressEditForm();
	}
	else
	{
		BuildEmptyState();
	}
}

void SSCOSCServerDetails::ClearSelection()
{
	CurrentEndpointItem.Reset();
	CurrentAddressItem.Reset();

	if (TitleTextBlock.IsValid())
	{
		TitleTextBlock->SetText(LOCTEXT("NoSelectionTitle", "No Selection"));
	}
	
	BuildEmptyState();
}

void SSCOSCServerDetails::BuildEndpointEditForm(bool bIsNewItem)
{
	if (!ContentContainer.IsValid() || !CurrentEndpointItem.IsValid())
	{
		return;
	}

	ContentContainer->ClearChildren();

	ContentContainer->AddSlot()
	.AutoHeight()
	.Padding(0.0f, 8.0f)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(0.0f, 0.0f, 8.0f, 0.0f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("ServerNameLabel", "Server Name:"))
			.MinDesiredWidth(80.0f)
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			SAssignNew(ServerNameTextBox, SEditableTextBox)
			.Text(FText::FromName(CurrentEndpointItem->ServerName))
		]
	];

	ContentContainer->AddSlot()
	.AutoHeight()
	.Padding(0.0f, 8.0f)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(0.0f, 0.0f, 8.0f, 0.0f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("IPAddressLabel", "IP Address:"))
			.MinDesiredWidth(80.0f)
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			SAssignNew(IPAddressTextBox, SEditableTextBox)
			.Text(FText::FromString(CurrentEndpointItem->ServerConfig.IPAddress))
		]
	];

	ContentContainer->AddSlot()
	.AutoHeight()
	.Padding(0.0f, 8.0f)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(0.0f, 0.0f, 8.0f, 0.0f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("PortLabel", "Port:"))
			.MinDesiredWidth(80.0f)
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			SAssignNew(PortTextBox, SEditableTextBox)
			.Text(FText::FromString(FString::FromInt(CurrentEndpointItem->ServerConfig.Port)))
		]
	];

	ContentContainer->AddSlot()
	.AutoHeight()
	.Padding(0.0f, 8.0f)
	[
		SAssignNew(IsEnabledCheckBox, SCheckBox)
		.IsChecked(CurrentEndpointItem->ServerConfig.bIsEnabled ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("IsEnabledLabel", "Enable"))
		]
	];

	ContentContainer->AddSlot()
	.AutoHeight()
	.Padding(0.0f, 16.0f, 0.0f, 0.0f)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(0.0f, 0.0f, 8.0f, 0.0f)
		[
			SAssignNew(SaveButton, SButton)
			.Text(LOCTEXT("SaveButton", "Save"))
			.OnClicked(this, &SSCOSCServerDetails::OnSaveClicked, bIsNewItem)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SAssignNew(CancelButton, SButton)
			.Text(LOCTEXT("CancelButton", "Cancel"))
			.OnClicked(this, &SSCOSCServerDetails::OnCancelClicked, bIsNewItem)
		]
	];
}

void SSCOSCServerDetails::BuildAddressEditForm()
{
	if (!ContentContainer.IsValid() || !CurrentAddressItem.IsValid())
	{
		return;
	}

	ContentContainer->ClearChildren();

	ContentContainer->AddSlot()
	.AutoHeight()
	.Padding(0.0f, 8.0f)
	[
		SNew(STextBlock)
		.Text(LOCTEXT("Placeholder", "Placeholder for OSC Address detail panel"))
		.AutoWrapText(true)
	];
}

void SSCOSCServerDetails::BuildEmptyState()
{
	if (!ContentContainer.IsValid())
	{
		return;
	}

	ContentContainer->ClearChildren();

	ContentContainer->AddSlot()
	.FillHeight(1.0f)
	.VAlign(VAlign_Center)
	[
		SNew(STextBlock)
		.Text(LOCTEXT("NoSelectionContent", "Select an OSC Server or Address to view and edit details"))
		.AutoWrapText(true)
		.Justification(ETextJustify::Center)
	];
}

FReply SSCOSCServerDetails::OnSaveClicked(bool bIsNewItem)
{
	if (!CurrentEndpointItem.IsValid())
		return FReply::Handled();

	// Get values from form
	FName NewServerName = FName(*ServerNameTextBox->GetText().ToString());
	FString NewIPAddress = IPAddressTextBox->GetText().ToString();
	int32 NewPort = FCString::Atoi(*PortTextBox->GetText().ToString());
	bool bNewIsEnabled = IsEnabledCheckBox->IsChecked();

	// Validate if server name is unique and not empty
	if (NewServerName.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Server name can't be empty."));
		return FReply::Handled();
	}
	if (USCOSCServerSettings* ServerSettings = GetMutableDefault<USCOSCServerSettings>())
	{
		if (bIsNewItem)
		{
			// Check if name already exists
			if (ServerSettings->ServerParameters.ServerConfigs.Contains(NewServerName))
			{
				UE_LOG(LogTemp, Warning, TEXT("Server name already exists."));
				return FReply::Handled();
			}
		}
		else
		{
			// Existing item, check if name changed and if new name already exists
			if (NewServerName != OriginalServerName && ServerSettings->ServerParameters.ServerConfigs.Contains(NewServerName))
			{
				UE_LOG(LogTemp, Warning, TEXT("Server name already exists."));
				return FReply::Handled();
			}
		}
	}

	// Validate port range
	if (NewPort < 1024 || NewPort > 65535)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid port number: %d. Must be between 1024 and 65535."), NewPort);
		return FReply::Handled();
	}

	// Update settings
	if (USCOSCServerSettings* ServerSettings = GetMutableDefault<USCOSCServerSettings>())
	{
		// For existing items, remove old entry if name changed
		// For new items, don't remove anything
		if (!bIsNewItem && NewServerName != OriginalServerName)
		{
			ServerSettings->ServerParameters.ServerConfigs.Remove(OriginalServerName);
		}

		// Add/update new entry
		FSCOSCServerConfig NewConfig(NewIPAddress, (uint16)NewPort, bNewIsEnabled);
		ServerSettings->ServerParameters.ServerConfigs.Add(NewServerName, NewConfig);

		// Save to disk
		ServerSettings->SaveConfig();

		// Existing endpoint
		// Update current item
		CurrentEndpointItem->ServerName = NewServerName;
		CurrentEndpointItem->ServerConfig = NewConfig;

		// Update original values to the newly saved state (for future cancel operations)
		OriginalServerName = NewServerName;
		OriginalServerConfig = NewConfig;

		// Update title
		if (TitleTextBlock.IsValid())
		{
			TitleTextBlock->SetText(FText::Format(LOCTEXT("EndpointTitle", "OSC Server: {0}"), FText::FromName(NewServerName)));
		}
		
		if (bIsNewItem)
		{
			// New endpoint
			// Execute delegate to update server list
			// TODO and select the new item in list
			// for now just clear selection
			ClearSelection();
			OnServerSettingsSavedDelegate.ExecuteIfBound(true /*bIsNewItem*/);
		}
		else
		{
			// Execute delegate to update server list
			OnServerSettingsSavedDelegate.ExecuteIfBound(false /*bIsNewItem*/);
		}
		
		// Notify server manager if game is running
		NotifyRuntimeServerManager(NewServerName, NewConfig);

		UE_LOG(LogTemp, Log, TEXT("Saved OSC Server: %s (%s:%d)"), *NewServerName.ToString(), *NewIPAddress, NewPort);
	}

	return FReply::Handled();
}

FReply SSCOSCServerDetails::OnCancelClicked(bool bIsNewItem)
{
	if (!CurrentEndpointItem.IsValid())
		return FReply::Handled();

	if (bIsNewItem)
	{
		// New endpoint
		// Return to empty state
		ClearSelection();
	}
	else
	{
		// Existing endpoint
		// Restore original values to form
		if (ServerNameTextBox.IsValid())
		{
			ServerNameTextBox->SetText(FText::FromName(OriginalServerName));
		}
		if (IPAddressTextBox.IsValid())
		{
			IPAddressTextBox->SetText(FText::FromString(OriginalServerConfig.IPAddress));
		}
		if (PortTextBox.IsValid())
		{
			PortTextBox->SetText(FText::FromString(FString::FromInt(OriginalServerConfig.Port)));
		}
		if (IsEnabledCheckBox.IsValid())
		{
			IsEnabledCheckBox->SetIsChecked(OriginalServerConfig.bIsEnabled ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Cancelled changes to OSC Server: %s"), *OriginalServerName.ToString());

	return FReply::Handled();
}

void SSCOSCServerDetails::NotifyRuntimeServerManager(const FName& ServerName, const FSCOSCServerConfig& Config)
{
	// Notify if game is running
	if (GEditor && GEditor->GetPIEWorldContext())
	{
		USCOSCServerManager* ServerManager = GEditor->GetPIEWorldContext()->World()->GetGameInstance()->GetSubsystem<USCOSCServerManager>();
		if (ServerManager)
		{
			// Update server endpoint if exists
			if (ServerManager->GetOSCServer(ServerName))
			{
				ServerManager->StopServer(ServerName);
				ServerManager->SetServerEndpoint(ServerName, Config.IPAddress, Config.Port);
				// Start server again if set to enabled
				if (Config.bIsEnabled)
				{
					ServerManager->StartServer(ServerName);
				}
				UE_LOG(LogTemp, Log, TEXT("Updated runtime server endpoint: %s (%s:%d)"), *ServerName.ToString(), *Config.IPAddress, Config.Port);
			}
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
