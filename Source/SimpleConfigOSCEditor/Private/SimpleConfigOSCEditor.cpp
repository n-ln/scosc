#include "SimpleConfigOSCEditor.h"

static const FName SCOSCEditorTabName("Simple Config OSC");

#define LOCTEXT_NAMESPACE "FSimpleConfigOSCEditorModule"

void FSimpleConfigOSCEditorModule::StartupModule()
{
	// Register menu entry

	// Register nomad tab spawner
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SCOSCEditorTabName,
		FOnSpawnTab::CreateRaw(this, &FSimpleConfigOSCEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("DockableTabTitle", "SCOSC Editor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	// Test - invoke tab
	FGlobalTabmanager::Get()->TryInvokeTab(SCOSCEditorTabName);
}

void FSimpleConfigOSCEditorModule::ShutdownModule()
{
    // Unregister menus

	// Unregister tab spawner
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SCOSCEditorTabName);
}

void FSimpleConfigOSCEditorModule::RegisterMenus()
{
	
}

void FSimpleConfigOSCEditorModule::OnMenuButtonClicked()
{
	
}

TSharedRef<SDockTab> FSimpleConfigOSCEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	// Create plugin editor tab
	return SNew(SDockTab);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSimpleConfigOSCEditorModule, SimpleConfigOSCEditor)