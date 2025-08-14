// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCServerDetails.h"

#include "SlateOptMacros.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Styling/CoreStyle.h"

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
				SAssignNew(ContentTextBlock, STextBlock)
				.Text(LOCTEXT("NoSelectionContent", "Select an OSC Server or Address to view and edit details"))
				.AutoWrapText(true)
			]
		]
	];
}

void SSCOSCServerDetails::SetSelectedEndpoint(TSharedPtr<FSCOSCServerEndpointListItem> EndpointItem)
{
	CurrentEndpointItem = EndpointItem;
	CurrentAddressItem.Reset();

	if (EndpointItem.IsValid())
	{
		if (TitleTextBlock.IsValid())
		{
			TitleTextBlock->SetText(FText::Format(LOCTEXT("EndpointTitle", "OSC Server: {0}"), FText::FromName(EndpointItem->ServerName)));
		}
		
		if (ContentTextBlock.IsValid())
		{
			FString ContentString = FString::Printf(TEXT("Server Name: %s\nIP Address: %s\nPort: %d\nEnabled by Default: %s"),
				*EndpointItem->ServerName.ToString(),
				*EndpointItem->ServerConfig.IPAddress,
				EndpointItem->ServerConfig.Port,
				EndpointItem->ServerConfig.bEnableByDefault ? TEXT("Yes") : TEXT("No"));
			
			ContentTextBlock->SetText(FText::FromString(ContentString));
		}
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
		
		if (ContentTextBlock.IsValid())
		{
			FString ContentString = FString::Printf(TEXT("OSC Address: %s\nSelected: %s"),
				*AddressItem->OSCAddress,
				AddressItem->bIsSelected ? TEXT("Yes") : TEXT("No"));
			
			ContentTextBlock->SetText(FText::FromString(ContentString));
		}
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
	
	if (ContentTextBlock.IsValid())
	{
		ContentTextBlock->SetText(LOCTEXT("NoSelectionContent", "Select an OSC Server or Address to view and edit details"));
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
