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
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("EditorTitle", "SOCSC Editor"))
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("EditorAddrList", "OSC Address List"))
				]
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("EditorDetail", "OSC Details"))
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(4.f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("EditorStatus", "OSC Status"))
				]
			]
		];
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSimpleConfigOSCEditorModule, SimpleConfigOSCEditor)