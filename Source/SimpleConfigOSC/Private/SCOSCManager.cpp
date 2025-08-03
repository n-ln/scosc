// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCManager.h"

#include "OSCServer.h"
#include "OSCClient.h"


// Sets default values
ASCOSCManager::ASCOSCManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsListening = false;
}

// Called when the game starts or when spawned
void ASCOSCManager::BeginPlay()
{
	Super::BeginPlay();

	//Create OSC Server
	OSCServer = NewObject<UOSCServer>();
	OSCServer->SetAddress(ListenAddress, ListenPort);
	SetServerPort(ListenPort);
	UE_LOG(LogTemp, Warning, TEXT("Current status: %s"), OSCServer->IsActive() ? TEXT("Active") : TEXT("Inactive"));
	StartServer();
	UE_LOG(LogTemp, Warning, TEXT("Current status: %s"), OSCServer->IsActive() ? TEXT("Active") : TEXT("Inactive"));
	UE_LOG(LogTemp, Warning, TEXT("OSC Server listening on %s:%d"), *OSCServer->GetIpAddress(false), OSCServer->GetPort());

	// Bind to OnOscMessageReceived
	OSCServer->OnOscMessageReceived.AddDynamic(this, &ASCOSCManager::HandleReceivedMessage);
}

// Called every frame
void ASCOSCManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASCOSCManager::StartServer()
{
	if (OSCServer)
	{
		OSCServer->Listen();
		bIsListening = true;
		UE_LOG(LogTemp, Warning, TEXT("OSC Server started on %s:%d"), *ListenAddress, ListenPort);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Server not initialized"));
	}
}

void ASCOSCManager::StopServer()
{
	if (OSCServer)
	{
		OSCServer->Stop();
		bIsListening = false;
		UE_LOG(LogTemp, Warning, TEXT("OSC Server stopped"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Server not initialized"));
	}
}

void ASCOSCManager::SetServerPort(uint16 Port)
{
	ListenPort = Port;
	if (OSCServer)
	{
		OSCServer->SetAddress(ListenAddress, ListenPort);
		UE_LOG(LogTemp, Warning, TEXT("OSC Server port set to %d"), ListenPort);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Server not initialized"));
	}
}

void ASCOSCManager::HandleReceivedMessage(const FOSCMessage& Message, const FString& IPAddress, const int32 Port)
{
	UE_LOG(LogTemp, Warning, TEXT("Received OSC Message: %s from %s:%d"), *Message.GetAddress().GetFullPath(), *IPAddress, Port);
}

void ASCOSCManager::RegisterListener(UObject* Object, TArray<FString> ListenAddresses)
{
	//Log object name
	UE_LOG(LogTemp, Warning, TEXT("Registering listener for object: %s"), *Object->GetName());
}

void ASCOSCManager::UnregisterListener(UObject* Object, TArray<FString> ListenAddresses)
{
	//Log object name
	UE_LOG(LogTemp, Warning, TEXT("Unregistering listener for object: %s"), *Object->GetName());
}

