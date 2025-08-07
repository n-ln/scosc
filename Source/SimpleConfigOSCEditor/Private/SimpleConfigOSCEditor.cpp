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