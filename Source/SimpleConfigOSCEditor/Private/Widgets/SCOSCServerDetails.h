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
	void SetSelectedEndpoint(TSharedPtr<FSCOSCServerEndpointListItem> EndpointItem, bool bIsNewItem);
	void SetSelectedAddress(TSharedPtr<FSCOSCServerAddressListItem> AddressItem);
	void ClearSelection();

	// Delegate for notifying when settings are saved
	DECLARE_DELEGATE_OneParam(FOnServerSettingsSaved, bool /*bIsNewItem*/);
	// Delegate accessor
	FOnServerSettingsSaved& OnServerSettingsSaved() { return OnServerSettingsSavedDelegate; }

private:
	// UI Elements
	TSharedPtr<STextBlock> TitleTextBlock;
	TSharedPtr<SVerticalBox> ContentContainer;

	// Form fields for server editing
	TSharedPtr<SEditableTextBox> ServerNameTextBox;
	TSharedPtr<SEditableTextBox> IPAddressTextBox;
	TSharedPtr<SEditableTextBox> PortTextBox;
	TSharedPtr<SCheckBox> IsEnabledCheckBox;
	TSharedPtr<SButton> SaveButton;
	TSharedPtr<SButton> CancelButton;

	// Current selection state
	TSharedPtr<FSCOSCServerEndpointListItem> CurrentEndpointItem;
	TSharedPtr<FSCOSCServerAddressListItem> CurrentAddressItem;

	// Original values for cancel functionality
	FName OriginalServerName;
	FSCOSCServerConfig OriginalServerConfig;

	// Delegate instance
	FOnServerSettingsSaved OnServerSettingsSavedDelegate;

	// Methods
	void BuildEndpointEditForm(bool bIsNewItem);
	void BuildAddressEditForm();
	void BuildEmptyState();
	
	FReply OnSaveClicked(bool bIsNewItem);
	FReply OnCancelClicked(bool bIsNewItem);
	FReply OnDeleteClicked();
	
	void StopRuntimeServer(const FName& ServerName);
	void AddOrUpdateRuntimeServer(const FName& ServerName, const FSCOSCServerConfig& Config);
};
