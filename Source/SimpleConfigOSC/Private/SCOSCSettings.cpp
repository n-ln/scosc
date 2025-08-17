// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCSettings.h"


USCOSCPluginSettings::USCOSCPluginSettings()
{
	
}

USCOSCProjectSettings::USCOSCProjectSettings()
{
	ProjectParameters.bShowUserSettings = false;
}

USCOSCServerSettings::USCOSCServerSettings()
{
	ServerParameters.bEnableServerMain = false;
	TempEnsureDefaultServer();
}

void USCOSCServerSettings::TempEnsureDefaultServer()
{
	if (ServerParameters.ServerConfigs.Num() == 0)
	{
		FSCOSCServerConfig DefaultConfig(FString("0.0.0.0"), 38000, true);
		ServerParameters.ServerConfigs.Add(FName("DefaultServer"), DefaultConfig);
	}
}

USCOSCClientSettings::USCOSCClientSettings()
{
	ClientParameters.bEnableClientMain = false;
}
