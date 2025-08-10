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
	ListTitle = InArgs._ListTitle;
	DetailsTitle = InArgs._DetailsTitle;
	ListSource = InArgs._ListSource;

	ChildSlot
	[
		SNew(SSplitter)
		.Orientation(Orient_Horizontal)
		+ SSplitter::Slot()
		.Value(0.35f)
		[
			SNew(SBorder)
			.BorderImage(FStyleDefaults::GetNoBrush())
			.Padding(4.f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.f, 0.f, 0.f, 4.f)
				[
					/*
					SNew(STextBlock)
					.Text(ListTitle)
					.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
					*/
					// Tool bar content
					InArgs._ToolBar.Widget
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.f)
				[
					SNew(SListView<TSharedPtr<FString>>)
					.SelectionMode(ESelectionMode::Single)
					.ListItemsSource(ListSource.Get())
				]
			]
		]
		+ SSplitter::Slot()
		.Value(0.65f)
		[
			SNew(SBorder)
			.BorderImage(FStyleDefaults::GetNoBrush())
			.Padding(4.f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.f, 0.f, 0.f, 4.f)
				[
					SNew(STextBlock)
					.Text(DetailsTitle)
					.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.f)
				[
					// Details content
					InArgs._DetailsContent.Widget
				]
			]
		]
	];
}