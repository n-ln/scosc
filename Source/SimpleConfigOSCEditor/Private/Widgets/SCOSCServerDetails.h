// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SCOSCServerLists.h"

/**
 * 
 */
class SIMPLECONFIGOSCEDITOR_API SSCOSCServerDetails : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSCOSCServerDetails)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// Update current selected item
	void SetSelectedEndpoint(TSharedPtr<FSCOSCServerEndpointListItem> EndpointItem);
	void SetSelectedAddress(TSharedPtr<FSCOSCServerAddressListItem> AddressItem);
	void ClearSelection();

private:
	// UI Elements
	TSharedPtr<STextBlock> TitleTextBlock;
	TSharedPtr<STextBlock> ContentTextBlock;

	// Current selection state
	TSharedPtr<FSCOSCServerEndpointListItem> CurrentEndpointItem;
	TSharedPtr<FSCOSCServerAddressListItem> CurrentAddressItem;
};
