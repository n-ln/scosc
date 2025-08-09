#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SSCOSCEditorWidget : public SCompoundWidget
{
public:
	// Slate arguments
	SLATE_BEGIN_ARGS(SSCOSCEditorWidget)
		{}
		SLATE_ARGUMENT(TSharedPtr<TArray<TSharedPtr<FString>>>, OSCAddressList)
		SLATE_ARGUMENT(TSharedPtr<TArray<TSharedPtr<FString>>>, OSCDestinationList)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	// Data sources from module
	TSharedPtr<TArray<TSharedPtr<FString>>> OSCAddressList;
	TSharedPtr<TArray<TSharedPtr<FString>>> OSCDestinationList;
};