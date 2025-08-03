// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCOSCManager.generated.h"

class UOSCServer;
class UOSCClient;

UCLASS()
class SIMPLECONFIGOSC_API ASCOSCManager : public AActor
{
	GENERATED_BODY()
	
	//TODO: Singleton

public:
	// Sets default values for this actor's properties
	ASCOSCManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

private:


	UOSCServer* OSCServer;
	UOSCClient* OSCClient;

	FString ListenAddress = TEXT("0.0.0.0");
	uint16 ListenPort = 38000;

	FString TargetAddress;
	uint16 TargetPort;

	bool bIsListening;

	//TODO Registered Listeners Map
};
