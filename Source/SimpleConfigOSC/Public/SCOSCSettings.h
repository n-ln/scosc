// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCOSCParameters.h"
#include "UObject/Object.h"
#include "SCOSCSettings.generated.h"

/**
 * 
 */

UCLASS(Config = PluginSettings, MinimalAPI)
class USCOSCPluginSettings : public UObject
{
	GENERATED_BODY()

public:

	USCOSCPluginSettings();

private:
};

UCLASS(Config = PluginPerProjectSettings, MinimalAPI)
class USCOSCProjectSettings : public UObject
{
	GENERATED_BODY()

public:

	USCOSCProjectSettings();

	UPROPERTY(Config)
	FSCOSCProjectParameters ProjectParameters;

private:
};

UCLASS(Config = OSCServerSettings, MinimalAPI)
class USCOSCServerSettings : public UObject
{
	GENERATED_BODY()
	
public:

	USCOSCServerSettings();

	UPROPERTY(Config)
	FSCOSCServerParameters ServerParameters;

private:
	// Create default server
	void TempEnsureDefaultServer();
};

UCLASS(Config = OSCClientSettings, MinimalAPI)
class USCOSCClientSettings : public UObject
{
	GENERATED_BODY()

public:

	USCOSCClientSettings();

	UPROPERTY(Config)
	FSCOSCClientParameters ClientParameters;

private:
};