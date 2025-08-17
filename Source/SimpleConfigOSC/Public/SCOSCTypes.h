// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SCOSCTypes.generated.h"

class UOSCServer;
/**
 * 
 */
UENUM(BlueprintType)
enum class EOSCDataType : uint8
{
	Int32 UMETA(DisplayName = "Integers"),
	Float32 UMETA(DisplayName = "Floats"),
	String UMETA(DisplayName = "Strings"),
	Blob UMETA(DisplayName = "Blobs")
};

USTRUCT()
struct FSCOSCServerConfig
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString IPAddress = "";
	UPROPERTY()
	uint16 Port = 0;
	UPROPERTY()
	bool bIsEnabled = false;

	FSCOSCServerConfig() = default;
	FSCOSCServerConfig(const FString& InIPAddress, uint16 InPort, bool bInIsEnabled = false)
		: IPAddress(InIPAddress), Port(InPort), bIsEnabled(bInIsEnabled) {}
};

USTRUCT()
struct FSCOSCServerRuntimeStatus
{
	GENERATED_BODY()
	
	UPROPERTY()
	UOSCServer* OSCServer = nullptr;
	UPROPERTY()
	bool bIsListening = false;
};

