// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "OSCMessage.h"

#include "SCOSCManagerSubsystem.generated.h"
 
class UOSCServer;
class UOSCClient;


UENUM(BlueprintType)
enum class EOSCDataType : uint8
{
	Int32 UMETA(DisplayName = "Integers"),
	Float32 UMETA(DisplayName = "Floats"),
	String UMETA(DisplayName = "Strings"),
	Blob UMETA(DisplayName = "Blobs")
};

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

	// Begin OSC server functionality
	UFUNCTION()
	void StartServer();
	UFUNCTION()
	void StopServer();

	UFUNCTION()
	void SetServerPort(uint16 Port);

	UFUNCTION()
	void HandleReceivedMessage(const FOSCMessage& Message, const FString& IPAddress, const int32 Port);

	// Register Listener
	UFUNCTION(BlueprintCallable)
	void RegisterListener(UObject* Object, const TArray<FString>& ListenAddresses);
	UFUNCTION(BlueprintCallable)
	void UnregisterListener(UObject* Object, const TArray<FString>& ListenAddresses);
	// End OSC server functionality

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

private:
	UPROPERTY()
	UOSCServer* OSCServer;

	UPROPERTY()
	TMap<FName, UOSCClient*> OSCClients;

	FString ListenAddress = TEXT("0.0.0.0");
	uint16 ListenPort = 38000;

	FString TargetAddress = TEXT("127.0.0.1");
	uint16 TargetPort = 39000;

	bool bIsListening;

	// Registered listeners
	TMap<FString, TArray<UObject*>> OSCListeners;
	// OSC data types of each address
	//TMap<FString, EOSCDataType> OSCDataTypes;
	
};
