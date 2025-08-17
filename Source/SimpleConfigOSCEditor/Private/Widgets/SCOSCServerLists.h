// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCOSCTypes.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */

struct FSCOSCServerEndpointListItem
{
	FName ServerName;
	FSCOSCServerConfig ServerConfig;
	bool bIsSelected = false;

	FSCOSCServerEndpointListItem() = default;
	FSCOSCServerEndpointListItem(const FName& InServerName, const FSCOSCServerConfig& InServerConfig, bool bInIsSelected = false)
		: ServerName(InServerName), ServerConfig(InServerConfig), bIsSelected(bInIsSelected) {}
};

struct FSCOSCServerAddressListItem
{
	FString OSCAddress;
	// TODO Implement OSC Address config
	bool bIsSelected = false;

	FSCOSCServerAddressListItem() = default;
	FSCOSCServerAddressListItem(const FString& InOSCAddress, bool bInIsSelected = false)
		: OSCAddress(InOSCAddress), bIsSelected(bInIsSelected) {}
};

// Delegates for list selection
DECLARE_DELEGATE_OneParam(FOnServerEndpointSelected, TSharedPtr<FSCOSCServerEndpointListItem>);
DECLARE_DELEGATE_OneParam(FOnServerAddressSelected, TSharedPtr<FSCOSCServerAddressListItem>);

class SIMPLECONFIGOSCEDITOR_API SSCOSCServerLists : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSCOSCServerLists)
		{
		}
		SLATE_ARGUMENT(TArray<TSharedPtr<FSCOSCServerEndpointListItem>>, EndpointListItems)
		SLATE_ARGUMENT(TArray<TSharedPtr<FSCOSCServerAddressListItem>>, AddressListItems)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// Settings management
	void RefreshFromSettings();

	// Delegate accessors
	FOnServerEndpointSelected& OnServerEndpointSelected() { return OnServerEndpointSelectedDelegate; }
	FOnServerAddressSelected& OnServerAddressSelected() { return OnServerAddressSelectedDelegate; }

private:
	TArray<TSharedPtr<FSCOSCServerEndpointListItem>> EndpointListItems;
	TArray<TSharedPtr<FSCOSCServerAddressListItem>> AddressListItems;

	FReply OnAddOSCEndpoint();
	FReply OnAddOSCAddress();

	TSharedRef<ITableRow> OnGenerateEndpointRow(TSharedPtr<FSCOSCServerEndpointListItem> Item, const TSharedRef<STableViewBase>& OwnerTable) const;
	TSharedRef<ITableRow> OnGenerateAddressRow(TSharedPtr<FSCOSCServerAddressListItem> Item, const TSharedRef<STableViewBase>& OwnerTable) const;

	void OnEndpointSelectionChanged(TSharedPtr<FSCOSCServerEndpointListItem> Item, ESelectInfo::Type SelectInfo);
	void OnAddressSelectionChanged(TSharedPtr<FSCOSCServerAddressListItem> Item, ESelectInfo::Type SelectInfo);

	// Delegates
	FOnServerEndpointSelected OnServerEndpointSelectedDelegate;
	FOnServerAddressSelected OnServerAddressSelectedDelegate;

	// Widget references for cross-selection clearing
	TSharedPtr<SListView<TSharedPtr<FSCOSCServerEndpointListItem>>> EndpointListView;
	TSharedPtr<SListView<TSharedPtr<FSCOSCServerAddressListItem>>> AddressListView;
};
