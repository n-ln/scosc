#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

// Forward declarations
class SSCOSCServerLists;
class SSCOSCServerDetails;
struct FSCOSCServerEndpointListItem;
struct FSCOSCServerAddressListItem;

class SSCOSCEditorWidget : public SCompoundWidget
{
public:

	~SSCOSCEditorWidget();
	
	// Slate arguments
	SLATE_BEGIN_ARGS(SSCOSCEditorWidget)
		{}
		SLATE_ARGUMENT(TSharedPtr<TArray<TSharedPtr<FString>>>, OSCAddressList)
		SLATE_ARGUMENT(TSharedPtr<TArray<TSharedPtr<FString>>>, OSCDestinationList)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	UPROPERTY(Config)
	bool bEnableServerMain;

	UPROPERTY(Config)
	bool bEnableClientMain;

	UPROPERTY(Config)
	bool bShowUserSettings;

private:
	// Data sources from module
	TSharedPtr<TArray<TSharedPtr<FString>>> OSCAddressList;
	TSharedPtr<TArray<TSharedPtr<FString>>> OSCDestinationList;

	ECheckBoxState GetServerMainCheckState() const;
	void ToggleServerMain(ECheckBoxState CheckState);

	ECheckBoxState GetClientMainCheckState() const;
	void ToggleClientMain(ECheckBoxState CheckState);

	ECheckBoxState GetSettingCheckState() const;
	void ToggleSetting(ECheckBoxState CheckState);
	
	FReply OnAddOSCDestinationAddress();

	// Widget references
	TSharedPtr<SSCOSCServerLists> ServerListsWidget;
	TSharedPtr<SSCOSCServerDetails> ServerDetailsWidget;

	// Delegate handlers
	// New creation
	void OnServerEndpointCreateNew(TSharedPtr<FSCOSCServerEndpointListItem> NewEndpointItem);
	// Existing
	void OnServerEndpointSelected(TSharedPtr<FSCOSCServerEndpointListItem> EndpointItem);
	void OnServerAddressSelected(TSharedPtr<FSCOSCServerAddressListItem> AddressItem);
	// Settings saved notification
	void OnServerSettingsSaved(bool bIsNewItem);
};