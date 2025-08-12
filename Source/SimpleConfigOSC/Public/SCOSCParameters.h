// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCOSCTypes.h"
#include "UObject/Object.h"
#include "SCOSCParameters.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSCOSCPluginParameters
{
	GENERATED_BODY()

	FSCOSCPluginParameters();

	
};


USTRUCT(BlueprintType)
struct FSCOSCProjectParameters
{
	GENERATED_BODY()

	FSCOSCProjectParameters();

	UPROPERTY(Config)
	bool bShowUserSettings;
};


USTRUCT(BlueprintType)
struct FSCOSCServerParameters
{
	GENERATED_BODY()

	FSCOSCServerParameters();

	UPROPERTY(Config)
	bool bEnableServerMain;
	UPROPERTY(Config)
	TMap<FName, FSCOSCServerConfig> ServerConfigs;
};

USTRUCT(BlueprintType)
struct FSCOSCClientParameters
{
	GENERATED_BODY()

	FSCOSCClientParameters();

	UPROPERTY(Config)
	bool bEnableClientMain;
};