#include "SimpleConfigOSCEditor.h"

static const FName SCOSCEditorTabName("Simple Config OSC");

#define LOCTEXT_NAMESPACE "FSimpleConfigOSCEditorModule"

void FSimpleConfigOSCEditorModule::StartupModule()
{
	// Register menu entry
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSimpleConfigOSCEditorModule::RegisterMenus));

	// Register nomad tab spawner
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SCOSCEditorTabName,
		FOnSpawnTab::CreateRaw(this, &FSimpleConfigOSCEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("DockableTabTitle", "SCOSC Editor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

}

void FSimpleConfigOSCEditorModule::ShutdownModule()
{
    // Unregister menu
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	// Unregister tab spawner
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SCOSCEditorTabName);
}

void FSimpleConfigOSCEditorModule::RegisterMenus()
{
	// Set owner for menus
	FToolMenuOwnerScoped OwnerScoped(this);

	// Add entry to top menu (Main Menu > Window)
	if (UToolMenu* MainMenuWindow = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window"))
	{
		FToolMenuSection& MainMenuSection = MainMenuWindow->FindOrAddSection("SCOSC", LOCTEXT("MenuSection", "SCOSC"));
		MainMenuSection.AddMenuEntry
		(
			"OpenEditor",
			LOCTEXT("OpenEditor", "Open SCOSC Editor"),
			LOCTEXT("OpenEditorTooltip", "Opens the Simple Config OSC Editor tab."),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"),
			FUIAction(FExecuteAction::CreateRaw(this, &FSimpleConfigOSCEditorModule::OnMenuButtonClicked))
		);
	}

	// Add button to editor toolbar
	if (UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User"))
	{
		FToolMenuSection& ToolbarSection = ToolbarMenu->FindOrAddSection("SCOSC", LOCTEXT("ToolbarSection", "Setting"));
		ToolbarSection.AddEntry(FToolMenuEntry::InitToolBarButton(
			"OpenEditor",
			FUIAction(FExecuteAction::CreateRaw(this, &FSimpleConfigOSCEditorModule::OnMenuButtonClicked)),
			LOCTEXT("OpenEditor", "Open SCOSC Editor"),
			LOCTEXT("OpenEditorTooltip", "Opens the Simple Config OSC Editor tab."),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details")
		));
	}
}

void FSimpleConfigOSCEditorModule::OnMenuButtonClicked()
{
	// Invoke editor tab
	FGlobalTabmanager::Get()->TryInvokeTab(SCOSCEditorTabName);
}

TSharedRef<SDockTab> FSimpleConfigOSCEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	// Create plugin editor tab
	return SNew(SDockTab)
	//.TabRole(ETabRole::NomadTab)
	//.Label(LOCTEXT("DockableTabTitle", "SCOSC Editor"))
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
				SNew(SSplitter)
				.Orientation(Orient_Horizontal)
				+ SSplitter::Slot()
				.Value(0.25f)
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
							.Text(LOCTEXT("EditorAddrList", "OSC Address List"))
							.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
						]
						+ SVerticalBox::Slot()
						.FillHeight(1.f)
						[
							SNew(SListView<TSharedPtr<FString>>)
							.SelectionMode(ESelectionMode::Single)
							.ListItemsSource(&OSCAddressList)
						]
					]
				]
				+ SSplitter::Slot()
				.Value(0.75f)
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
							.Text(LOCTEXT("EditorServerDetail", "OSC Server Details"))
							.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
						]
						+ SVerticalBox::Slot()
						.FillHeight(1.f)
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
				SNew(SSplitter)
				.Orientation(Orient_Horizontal)
				+ SSplitter::Slot()
				.Value(0.25f)
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
							.Text(LOCTEXT("EditorDestList", "OSC Destination List"))
							.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
						]
						+ SVerticalBox::Slot()
						.FillHeight(1.f)
						[
							SNew(SListView<TSharedPtr<FString>>)
							.SelectionMode(ESelectionMode::Single)
							.ListItemsSource(&OSCDestinationList)
						]
					]
				]
				+ SSplitter::Slot()
				.Value(0.75f)
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
							.Text(LOCTEXT("EditorClientDetail", "OSC Client Details"))
							.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
						]
						+ SVerticalBox::Slot()
						.FillHeight(1.f)
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
    
IMPLEMENT_MODULE(FSimpleConfigOSCEditorModule, SimpleConfigOSCEditor)