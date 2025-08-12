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
};

struct FSCOSCServerAddressListItem
{
	FString OSCAddress;
	// TODO Implement OSC Address config
	bool bIsSelected = false;
};

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

private:
	TArray<TSharedPtr<FSCOSCServerEndpointListItem>> EndpointListItems;
	TArray<TSharedPtr<FSCOSCServerAddressListItem>> AddressListItems;

	FReply OnAddOSCEndpoint();
	FReply OnAddOSCAddress();
};
