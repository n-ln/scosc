// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SCOSCManagerSubsystem.generated.h"

class UOSCServer;
class UOSCClient;

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
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override
	{
		return true;
		//TODO: custom control
	}
	// End UGameInstanceSubsystem Interface

	//TODO: Move OSC Manager implementation
	// Begin OSC server functionality
	void StartServer();
	void StopServer();

	void SetServerPort(uint16 Port);

	UFUNCTION()
	void HandleReceivedMessage(const FOSCMessage& Message, const FString& IPAddress, const int32 Port);

	//TODO Register Listener
	UFUNCTION(BlueprintCallable)
	void RegisterListener(UObject* Object, TArray<FString> ListenAddresses);
	UFUNCTION(BlueprintCallable)
	void UnregisterListener(UObject* Object, TArray<FString> ListenAddresses);
	// End OSC server functionality

private:
	UPROPERTY()
	UOSCServer* OSCServer;
	
	UPROPERTY()
	UOSCClient* OSCClient;

	FString ListenAddress = TEXT("0.0.0.0");
	uint16 ListenPort = 38000;

	FString TargetAddress;
	uint16 TargetPort;

	bool bIsListening;

	//TODO Registered Listeners Map
	
};
