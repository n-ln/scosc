#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSimpleConfigOSCEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void RegisterMenus();
    void OnMenuButtonClicked();

    TSharedRef<SDockTab> OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs);
};
