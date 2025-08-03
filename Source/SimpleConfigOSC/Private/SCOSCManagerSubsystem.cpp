// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCManagerSubsystem.h"

#include "OSCServer.h"
#include "OSCClient.h"

void USCOSCManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//TODO: Should add auto start logic?
	bIsListening = false;

	//Create OSC Server
	OSCServer = NewObject<UOSCServer>();
	OSCServer->SetAddress(ListenAddress, ListenPort);
	SetServerPort(ListenPort);
	StartServer();

	// Bind to OnOscMessageReceived
	OSCServer->OnOscMessageReceived.AddDynamic(this, &USCOSCManagerSubsystem::HandleReceivedMessage);

	UE_LOG(LogTemp, Warning, TEXT("OSC Manager Subsystem initialized"));

}

void USCOSCManagerSubsystem::Deinitialize()
{
	//TODO: Stop OSC server&client
	StopServer();

	UE_LOG(LogTemp, Warning, TEXT("OSC Manager Subsystem deinitialized"));
	
	Super::Deinitialize();
}

void USCOSCManagerSubsystem::StartServer()
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

void USCOSCManagerSubsystem::StopServer()
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

void USCOSCManagerSubsystem::SetServerPort(uint16 Port)
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

void USCOSCManagerSubsystem::HandleReceivedMessage(const FOSCMessage& Message, const FString& IPAddress, const int32 Port)
{
	UE_LOG(LogTemp, Warning, TEXT("Received OSC Message: %s from %s:%d"), *Message.GetAddress().GetFullPath(), *IPAddress, Port);
}

void USCOSCManagerSubsystem::RegisterListener(UObject* Object, TArray<FString> ListenAddresses)
{
	//Log object name
	UE_LOG(LogTemp, Warning, TEXT("Registering listener for object: %s"), *Object->GetName());
}

void USCOSCManagerSubsystem::UnregisterListener(UObject* Object, TArray<FString> ListenAddresses)
{
	//Log object name
	UE_LOG(LogTemp, Warning, TEXT("Unregistering listener for object: %s"), *Object->GetName());
}


