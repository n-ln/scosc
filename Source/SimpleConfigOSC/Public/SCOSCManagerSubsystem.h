// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SCOSCManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLECONFIGOSC_API USCOSCManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Begin UGameInstanceSubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End UGameInstanceSubsystem Interface

	//TODO: Move OSC Manager implementation

private:
	
	
};
