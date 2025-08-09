#include "SimpleConfigOSCEditor.h"
#include "Widgets/SCOSCEditorWidget.h"

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
	// Create plugin editor tab with new widget
	return SNew(SDockTab)
	[
		SNew(SSCOSCEditorWidget)
		.OSCAddressList(TSharedPtr<TArray<TSharedPtr<FString>>>(&OSCAddressList, [](TArray<TSharedPtr<FString>>*){}))
		.OSCDestinationList(TSharedPtr<TArray<TSharedPtr<FString>>>(&OSCDestinationList, [](TArray<TSharedPtr<FString>>*){}))
	];
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSimpleConfigOSCEditorModule, SimpleConfigOSCEditor)