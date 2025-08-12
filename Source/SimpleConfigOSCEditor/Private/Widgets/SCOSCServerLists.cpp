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
					SNew(SListView<TSharedPtr<FSCOSCServerEndpointListItem>>)

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
					SNew(SListView<TSharedPtr<FSCOSCServerAddressListItem>>)
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

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
