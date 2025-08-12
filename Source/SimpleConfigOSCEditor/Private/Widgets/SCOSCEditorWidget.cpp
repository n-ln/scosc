#include "./Widgets/SCOSCEditorWidget.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h" 
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/Text/TextLayout.h"
#include "SPositiveActionButton.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleDefaults.h"

#include "EditorFontGlyphs.h"
#include "SCOSCServerLists.h"
#include "SCOSCServerManager.h"
#include "SCOSCSettings.h"
#include "./Widgets/SCOSCEditorPanel.h"

#define LOCTEXT_NAMESPACE "SSCOSCEditorWidget"

SSCOSCEditorWidget::~SSCOSCEditorWidget()
{
	bEnableServerMain = false;
	bEnableClientMain = false;
	bShowUserSettings = false;
}

void SSCOSCEditorWidget::Construct(const FArguments& InArgs)
{
	// Input arguments
	OSCAddressList = InArgs._OSCAddressList;
	OSCDestinationList = InArgs._OSCDestinationList;

	ChildSlot
	[
		SNew(SVerticalBox)
		// Top bar
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.f)
		[
			SNew(SBorder)
			//.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			.BorderImage(new FSlateColorBrush(FSlateColor(EStyleColor::Panel)))
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SCheckBox)
					.Style(FAppStyle::Get(), "ToggleButtonCheckbox")
					.IsChecked(this, &SSCOSCEditorWidget::GetServerMainCheckState)
					.OnCheckStateChanged(this, &SSCOSCEditorWidget::ToggleServerMain)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Font(FAppStyle::Get().GetFontStyle("FontAwesome.14"))
							.Text(FEditorFontGlyphs::Caret_Down)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(4.f, 0.f, 0.f, 0.f)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("ToggleOSCServer", "Toggle Receive OSC"))
						]
					]
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(8.f, 0.f, 0.f, 0.f)
				[
					SNew(SCheckBox)
					.Style(FAppStyle::Get(), "ToggleButtonCheckbox")
					.IsChecked(this, &SSCOSCEditorWidget::GetClientMainCheckState)
					.OnCheckStateChanged(this, &SSCOSCEditorWidget::ToggleClientMain)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Font(FAppStyle::Get().GetFontStyle("FontAwesome.14"))
							.Text(FEditorFontGlyphs::Caret_Up)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.Padding(4.f, 0.f, 0.f, 0.f)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("ToggleOSCClient", "Toggle Send OSC"))
						]
					]
				]

				+ SHorizontalBox::Slot()
				[
					SNew(SSpacer)
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SCheckBox)
					.Style(FAppStyle::Get(), "ToggleButtonCheckbox")
					.IsChecked(this, &SSCOSCEditorWidget::GetSettingCheckState)
					.OnCheckStateChanged(this, &SSCOSCEditorWidget::ToggleSetting)
					[
						SNew(STextBlock)
						.Font(FAppStyle::Get().GetFontStyle("FontAwesome.14"))
						.Text(FEditorFontGlyphs::Cogs)
					]
				]
			]
		]

		+ SVerticalBox::Slot()
		.Padding(2.f)
		[
			SNew(SSplitter)
			.Orientation(Orient_Vertical)
			+ SSplitter::Slot()
			.Value(0.5f)
			[
				// OSC Server
				SNew(SBorder)
				.BorderImage(new FSlateColorBrush(FSlateColor(EStyleColor::Panel)))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Fill)
					[
						SNew(SBorder)
						.BorderImage(new FSlateColorBrush(FSlateColor(EStyleColor::Secondary)))
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							[
								SNew(STextBlock)
								.Text(LOCTEXT("EditorServerTitle", "OSC Server"))
								.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
							]
						]
					]
					+ SVerticalBox::Slot()
					.FillHeight(1.f)
					.Padding(0.f, 4.f, 0.f, 0.f)
					[
						SNew(SSCOSCEditorPanel)
						.ListTitle(LOCTEXT("EditorAddrList", "OSC Address List"))
						.DetailsTitle(LOCTEXT("EditorServerDetail", "OSC Server Details"))
						.ListSource(OSCAddressList)
						/*
						.ToolBar()
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							[
								SNew(SPositiveActionButton)
								//.OnGetMenuContent(this, &SSCOSCEditorWidget::OnAddOSCSourceAddress)
								.OnClicked(this, &SSCOSCEditorWidget::OnAddOSCSourceAddress)
								.Icon(FAppStyle::Get().GetBrush("Icons.Plus"))
								.Text(LOCTEXT("AddNewServerAddress", "OSC Source"))
							]
						]
						*/
						.ListContent()
						[
							SNew(SSCOSCServerLists)
						]
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
			]
			+ SSplitter::Slot()
			.Value(0.5f)
			[
				SNew(SBorder)
				.BorderImage(new FSlateColorBrush(FSlateColor(EStyleColor::Panel)))
				[
					// OSC Client
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Fill)
					[
						SNew(SBorder)
						.BorderImage(new FSlateColorBrush(FSlateColor(EStyleColor::Secondary)))
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							[
								SNew(STextBlock)
								.Text(LOCTEXT("EditorClientTitle", "OSC Client"))
								.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
							]
						]
					]
					+ SVerticalBox::Slot()
					.FillHeight(1.f)
					.Padding(0.f, 4.f, 0.f, 0.f)
					[
						SNew(SSCOSCEditorPanel)
						.ListTitle(LOCTEXT("EditorDestList", "OSC Destination List"))
						.DetailsTitle(LOCTEXT("EditorClientDetail", "OSC Client Details"))
						.ListSource(OSCDestinationList)
						.ToolBar()
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							[
								SNew(SPositiveActionButton)
								.OnClicked(this, &SSCOSCEditorWidget::OnAddOSCDestinationAddress)
								.Icon(FAppStyle::Get().GetBrush("Icons.Plus"))
								.Text(LOCTEXT("AddNewClientAddress", "OSC Destination"))
							]
						]
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
			]
		]

		// OSC Status
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.f)
		[
			SNew(SBorder)
			.BorderImage(new FSlateColorBrush(FSlateColor(EStyleColor::Panel)))
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("EditorStatus", "OSC Status"))
				]
			]
		]
	];
}

ECheckBoxState SSCOSCEditorWidget::GetServerMainCheckState() const
{
	return GetDefault<USCOSCServerSettings>()->ServerParameters.bEnableServerMain ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SSCOSCEditorWidget::ToggleServerMain(ECheckBoxState CheckState)
{
	USCOSCServerSettings* ServerSettings = GetMutableDefault<USCOSCServerSettings>();

	ServerSettings->ServerParameters.bEnableServerMain = !ServerSettings->ServerParameters.bEnableServerMain;
	
	if (GEditor->GetPIEWorldContext())
	{
		UE_LOG(LogTemp, Log, TEXT("PIE"));

		GEditor->GetPIEWorldContext()->World()->GetGameInstance()->GetSubsystem<USCOSCServerManager>()
			->ToggleServerMain(ServerSettings->ServerParameters.bEnableServerMain);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No PIE"));
	} 
}

ECheckBoxState SSCOSCEditorWidget::GetClientMainCheckState() const
{
	return GetDefault<USCOSCClientSettings>()->ClientParameters.bEnableClientMain ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SSCOSCEditorWidget::ToggleClientMain(ECheckBoxState CheckState)
{
	USCOSCClientSettings* ClientSettings = GetMutableDefault<USCOSCClientSettings>();
	
	// Simply flip the bool without check for now
	if (ClientSettings->ClientParameters.bEnableClientMain == true)
	{
		ClientSettings->ClientParameters.bEnableClientMain = false;
	}
	else
	{
		ClientSettings->ClientParameters.bEnableClientMain = true;
	}
}

ECheckBoxState SSCOSCEditorWidget::GetSettingCheckState() const
{
	return GetDefault<USCOSCProjectSettings>()->ProjectParameters.bShowUserSettings ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SSCOSCEditorWidget::ToggleSetting(ECheckBoxState CheckState)
{
	USCOSCProjectSettings* ProjectSettings = GetMutableDefault<USCOSCProjectSettings>();
	
	// Simply flip the bool without check for now
	if (ProjectSettings->ProjectParameters.bShowUserSettings == true)
	{
		ProjectSettings->ProjectParameters.bShowUserSettings = false;
	}
	else
	{
		ProjectSettings->ProjectParameters.bShowUserSettings = true;
	}
	
	// TODO: Save the settings
	//ProjectSettings->SaveConfig();
}

/*
FReply SSCOSCEditorWidget::OnAddOSCSourceAddress()
{
	// Placeholder for adding new OSC server address
	UE_LOG(LogTemp, Warning, TEXT("OSC Server new address clicked"));

	return FReply::Handled();
}
*/

FReply SSCOSCEditorWidget::OnAddOSCDestinationAddress()
{
	// Placeholder for adding new OSC client address
	UE_LOG(LogTemp, Warning, TEXT("OSC Client new address clicked"));

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE