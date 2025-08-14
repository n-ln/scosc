// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCServerLists.h"

#include "SlateOptMacros.h"
#include "SPositiveActionButton.h"

#define LOCTEXT_NAMESPACE "SSCOSCServerLists"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSCOSCServerLists::Construct(const FArguments& InArgs)
{
	// Input arguments
	EndpointListItems = InArgs._EndpointListItems;
	AddressListItems = InArgs._AddressListItems;

	// Temp hard coded list for testing
	EndpointListItems.Add(MakeShared<FSCOSCServerEndpointListItem>(FSCOSCServerEndpointListItem{ FName(TEXT("Default Server")), FSCOSCServerConfig(), false }));
	AddressListItems.Add(MakeShared<FSCOSCServerAddressListItem>(FSCOSCServerAddressListItem{ FString(TEXT("/text")), false}));
	
	ChildSlot
	[
		// Border Server list content
		SNew(SBorder)
		[
			SNew(SSplitter)
			.Orientation(Orient_Vertical)
			+ SSplitter::Slot()
			.Value(0.4f)
			[
				// Server
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					// Server toolbar
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SPositiveActionButton)
						//.OnGetMenuContent(this, &SSCOSCServerLists::OnAddOSCEndpoint)
						.OnClicked(this, &SSCOSCServerLists::OnAddOSCEndpoint)
						.Icon(FAppStyle::Get().GetBrush("Icons.Plus"))
						.Text(LOCTEXT("AddNewServerAddress", "OSC Server"))
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					// ListView
					SAssignNew(EndpointListView, SListView<TSharedPtr<FSCOSCServerEndpointListItem>>)
					.ListItemsSource(&EndpointListItems)
					.OnGenerateRow(this, &SSCOSCServerLists::OnGenerateEndpointRow)
					.OnSelectionChanged(this, &SSCOSCServerLists::OnEndpointSelectionChanged)
				]
			]
			+ SSplitter::Slot()
			.Value(0.6f)
			[
				// Address
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					// Address toolbar
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SPositiveActionButton)
						//.OnGetMenuContent(this, &SSCOSCServerLists::OnAddOSCAddress)
						.OnClicked(this, &SSCOSCServerLists::OnAddOSCAddress)
						.Icon(FAppStyle::Get().GetBrush("Icons.Plus"))
						.Text(LOCTEXT("AddNewServerAddress", "OSC Address"))
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					// ListView
					SAssignNew(AddressListView, SListView<TSharedPtr<FSCOSCServerAddressListItem>>)
					.ListItemsSource(&AddressListItems)
					.OnGenerateRow(this, &SSCOSCServerLists::OnGenerateAddressRow)
					.OnSelectionChanged(this, &SSCOSCServerLists::OnAddressSelectionChanged)
				]
			]
		]
	]; 
}

FReply SSCOSCServerLists::OnAddOSCEndpoint()
{
	// Placeholder for adding new OSC server endpoint
	UE_LOG(LogTemp, Warning, TEXT("OSC Server new endpoint clicked"));

	return FReply::Handled();
}

FReply SSCOSCServerLists::OnAddOSCAddress()
{
	// Placeholder for adding new OSC address
	UE_LOG(LogTemp, Warning, TEXT("OSC Address new address clicked"));

	return FReply::Handled();
}

TSharedRef<ITableRow> SSCOSCServerLists::OnGenerateEndpointRow(TSharedPtr<FSCOSCServerEndpointListItem> Item, const TSharedRef<STableViewBase>& OwnerTable) const
{
	return SNew(STableRow<TSharedPtr<FSCOSCServerEndpointListItem>>, OwnerTable)
		[
			SNew(STextBlock)
			.Text(FText::FromName(Item->ServerName))
		];
}

TSharedRef<ITableRow> SSCOSCServerLists::OnGenerateAddressRow(TSharedPtr<FSCOSCServerAddressListItem> Item, const TSharedRef<STableViewBase>& OwnerTable) const
{
	return SNew(STableRow<TSharedPtr<FSCOSCServerAddressListItem>>, OwnerTable)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Item->OSCAddress))
		];
}

void SSCOSCServerLists::OnEndpointSelectionChanged(TSharedPtr<FSCOSCServerEndpointListItem> Item, ESelectInfo::Type SelectInfo)
{
	if (Item.IsValid() && SelectInfo != ESelectInfo::Direct)
	{
		// Clear address list selection
		if (AddressListView.IsValid())
		{
			AddressListView->ClearSelection();
		}
		
		// Fire delegate
		OnServerEndpointSelectedDelegate.ExecuteIfBound(Item);
		
		UE_LOG(LogTemp, Log, TEXT("Selected OSC Server: %s"), *Item->ServerName.ToString());
	}
}

void SSCOSCServerLists::OnAddressSelectionChanged(TSharedPtr<FSCOSCServerAddressListItem> Item, ESelectInfo::Type SelectInfo)
{
	if (Item.IsValid() && SelectInfo != ESelectInfo::Direct)
	{
		// Clear endpoint list selection
		if (EndpointListView.IsValid())
		{
			EndpointListView->ClearSelection();
		}
		
		// Fire delegate
		OnServerAddressSelectedDelegate.ExecuteIfBound(Item);
		
		UE_LOG(LogTemp, Log, TEXT("Selected OSC Address: %s"), *Item->OSCAddress);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
