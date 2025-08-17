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
}

USCOSCClientSettings::USCOSCClientSettings()
{
	ClientParameters.bEnableClientMain = false;
}
