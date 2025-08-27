// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "OSCMessage.h"
#include "SCOSCTypes.h"

#include "SCOSCClientManager.generated.h"

class UOSCClient;

/**
 * 
 */
UCLASS()
class SIMPLECONFIGOSC_API USCOSCClientManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Begin UGameInstanceSubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override
	{
		return false;
		//TODO: custom control
	}
	// End UGameInstanceSubsystem Interface

	// Begin OSC client functionality
	UFUNCTION()
	UOSCClient* CreateClient(FName ClientName, const FString& IPAddress, uint16 Port);
	UFUNCTION()
	void DestroyClient(FName ClientName);

	UFUNCTION()
	void SetClientDestination(FName ClientName, const FString& IPAddress, uint16 Port);

	// TODO support different data types
	// For now, suppose float array
	UFUNCTION(BlueprintCallable)
	void SendOSCMessage(FName ClientName, const FString& Address, const TArray<float>& Message);
	// End OSC client functionality

private:
	UPROPERTY()
	TMap<FName, UOSCClient*> OSCClients;

	FString TargetAddress = TEXT("127.0.0.1");
	uint16 TargetPort = 39000;

	// Registered listeners
	TMap<FString, TArray<UObject*>> OSCListeners;
	// OSC data types of each address
	//TMap<FString, EOSCDataType> OSCDataTypes;
	
};
