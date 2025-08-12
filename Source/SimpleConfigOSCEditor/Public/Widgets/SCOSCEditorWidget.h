#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

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

	//FReply OnAddOSCSourceAddress();

	FReply OnAddOSCDestinationAddress();
	
};