#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Framework/Text/TextLayout.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleDefaults.h"

#include "./Widgets/SCOSCEditorWidget.h"
#include "./Widgets/SCOSCEditorPanel.h"

#define LOCTEXT_NAMESPACE "SSCOSCEditorWidget"

void SSCOSCEditorWidget::Construct(const FArguments& InArgs)
{
	// Input arguments
	OSCAddressList = InArgs._OSCAddressList;
	OSCDestinationList = InArgs._OSCDestinationList;

	ChildSlot
	[
		SNew(SVerticalBox)
		// Title
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("EditorTitle", "SCOSC Editor"))
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 14))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SSeparator)
		]
		// OSC Server
		+ SVerticalBox::Slot()
		.FillHeight(4.f)
		.Padding(4.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Toggle OSC Server"))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			.Padding(0.f, 8.f, 0.f, 0.f)
			[
				SNew(SSCOSCEditorPanel)
				.ListTitle(LOCTEXT("EditorAddrList", "OSC Address List"))
				.DetailsTitle(LOCTEXT("EditorServerDetail", "OSC Server Details"))
				.ListSource(OSCAddressList)
				.DetailsContent()
				[
					SNew(SScrollBox)
					+ SScrollBox::Slot()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0.f, 4.f)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Center)
							.Padding(0.f, 0.f, 8.f, 0.f)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("ServerPort", "Port:"))
							]
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							[
								SNew(SEditableTextBox)
								.Text(FText::FromString("8000"))
							]
						]
					]
				]
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SSeparator)
		]
		// OSC Client
		+ SVerticalBox::Slot()
		.FillHeight(4.f)
		.Padding(4.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SButton)
				.Text(FText::FromString("Toggle OSC Client"))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			.Padding(0.f, 8.f, 0.f, 0.f)
			[
				SNew(SSCOSCEditorPanel)
				.ListTitle(LOCTEXT("EditorDestList", "OSC Destination List"))
				.DetailsTitle(LOCTEXT("EditorClientDetail", "OSC Client Details"))
				.ListSource(OSCDestinationList)
				.DetailsContent()
				[
					SNew(SScrollBox)
					+ SScrollBox::Slot()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0.f, 4.f)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Center)
							.Padding(0.f, 0.f, 8.f, 0.f)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("ClientAddress", "Address:"))
							]
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							[
								SNew(SEditableTextBox)
								.Text(FText::FromString("127.0.0.1"))
							]
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0.f, 4.f)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Center)
							.Padding(0.f, 0.f, 8.f, 0.f)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("ClientPort", "Port:"))
							]
							+ SHorizontalBox::Slot()
							.FillWidth(1.f)
							[
								SNew(SEditableTextBox)
								.Text(FText::FromString("9000"))
							]
						]
					]
				]
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SSeparator)
		]
		// OSC Status
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("EditorStatus", "OSC Status"))
		]
	];
}

#undef LOCTEXT_NAMESPACE