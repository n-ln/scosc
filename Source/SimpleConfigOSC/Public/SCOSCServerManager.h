// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SCOSCTypes.h"
#include "SCOSCSettings.h"

#include "SCOSCServerManager.generated.h"

class UOSCServer;

/**
 * 
 */

UCLASS()
class SIMPLECONFIGOSC_API USCOSCServerManager : public UGameInstanceSubsystem
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

	// Begin OSC server functionality
	UFUNCTION()
	bool CreateServer(FName ServerName);
	UFUNCTION()
	UOSCServer* GetOSCServer(FName ServerName) const;
	UFUNCTION()
	void StartServer(FName ServerName);
	UFUNCTION()
	void StopServer(FName ServerName);
	UFUNCTION()
	void SetServerEndpoint(FName ServerName, const FString& Address, uint16 Port);

	UFUNCTION()
	void HandleReceivedMessage(const FOSCMessage& Message, const FString& IPAddress, const int32 Port);

	UFUNCTION()
	void ToggleServerMain(bool bEnable);

	// Register Listener
	UFUNCTION(BlueprintCallable)
	void RegisterListener(UObject* Object, const TArray<FString>& ListenAddresses);
	UFUNCTION(BlueprintCallable)
	void UnregisterListener(UObject* Object, const TArray<FString>& ListenAddresses);
	UFUNCTION()
	TArray<UObject*> GetAllListenersOfAddress(const FString& Address) const;
	UFUNCTION()
	void UnregisterAllListenersOfAddress(const FString& Address);
	// End OSC server functionality

private:
	UPROPERTY()
	TMap<FName, FSCOSCServerRuntimeStatus> OSCServers;

	USCOSCServerSettings* ServerSettings;
	
	// Registered listeners
	TMap<FString, TArray<UObject*>> OSCListeners;
	// OSC data types of each address
	//TMap<FString, EOSCDataType> OSCDataTypes;
};
