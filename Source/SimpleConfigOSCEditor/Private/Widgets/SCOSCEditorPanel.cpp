#include "./Widgets/SCOSCEditorPanel.h"

#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleDefaults.h"


void SSCOSCEditorPanel::Construct(const FArguments& InArgs)
{
	// Input arguments
	ListContent = InArgs._ListContent;
	DetailsContent = InArgs._DetailsContent;

	ChildSlot
	[
		SNew(SSplitter)
		.Orientation(Orient_Horizontal)
		+ SSplitter::Slot()
		.Value(0.4f)
		[
			InArgs._ListContent.Widget
		]
		+ SSplitter::Slot()
		.Value(0.6f)
		[
			InArgs._DetailsContent.Widget
		]
	];
}