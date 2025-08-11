// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SCOSCTypes.generated.h"

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