#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SSCOSCEditorPanel : public SCompoundWidget
{
public:
	// Slate arguments
	SLATE_BEGIN_ARGS(SSCOSCEditorPanel)
		: _ListTitle(FText::GetEmpty())
		, _DetailsTitle(FText::GetEmpty())
		{}
		SLATE_ARGUMENT(FText, ListTitle)
		SLATE_ARGUMENT(FText, DetailsTitle)
		SLATE_ARGUMENT(TSharedPtr<TArray<TSharedPtr<FString>>>, ListSource)
		SLATE_NAMED_SLOT(FArguments, ToolBar)
		SLATE_NAMED_SLOT(FArguments, ListContent)
		SLATE_NAMED_SLOT(FArguments, DetailsContent)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	// Configuration
	FText ListTitle;
	FText DetailsTitle;
	TSharedPtr<TArray<TSharedPtr<FString>>> ListSource;
};