// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCServerManager.h"

#include "OSCServer.h"
#include "OSCMessage.h"
#include "OSCManager.h"

void USCOSCServerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//TODO: Should add auto start logic?
	bIsListening = false;

	//Create OSC Server
	OSCServer = NewObject<UOSCServer>(this, FName("OSCServer"));
	//UE_LOG(LogTemp, Warning, TEXT("Outer object: %s"), *OSCServer->GetOuter()->GetName());
	OSCServer->SetAddress(ListenAddress, ListenPort);
	SetServerPort(ListenPort);
	StartServer();

	// Bind to OnOscMessageReceived
	OSCServer->OnOscMessageReceived.AddDynamic(this, &USCOSCServerManager::HandleReceivedMessage);

	UE_LOG(LogTemp, Warning, TEXT("OSC Server Manager initialized"));
}

void USCOSCServerManager::Deinitialize()
{
	StopServer();
	
	UE_LOG(LogTemp, Warning, TEXT("OSC Server Manager deinitialized"));
	
	Super::Deinitialize();
}

void USCOSCServerManager::StartServer()
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

void USCOSCServerManager::StopServer()
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

void USCOSCServerManager::SetServerPort(const uint16 Port)
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

void USCOSCServerManager::HandleReceivedMessage(const FOSCMessage& Message, const FString& IPAddress, const int32 Port)
{
	UE_LOG(LogTemp, Warning, TEXT("Received OSC Message: %s from %s:%d"), *Message.GetAddress().GetFullPath(), *IPAddress, Port);
}

void USCOSCServerManager::RegisterListener(UObject* Object, const TArray<FString>& ListenAddresses)
{
	for (const FString& Address : ListenAddresses)
	{
		if (!OSCListeners.Contains(Address))
		{
			OSCListeners.Add(Address, TArray<UObject*>());
		}
		OSCListeners.Find(Address)->AddUnique(Object);

		UE_LOG(LogTemp, Warning, TEXT("Registering listener %s for address: %s"), *Object->GetName(), *Address);
	}
}

void USCOSCServerManager::UnregisterListener(UObject* Object, const TArray<FString>& ListenAddresses)
{
	for (const FString& Address : ListenAddresses)
	{
		if (!OSCListeners.Contains(Address))
		{
			UE_LOG(LogTemp, Warning, TEXT("No listeners registered to address: %s"), *Address);
			continue;
		}
		if (!OSCListeners.Find(Address)->Contains(Object))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s not registered for address: %s"), *Object->GetName(), *Address);
			continue;
		}

		OSCListeners.Find(Address)->Remove(Object);
		UE_LOG(LogTemp, Warning, TEXT("Unregistered listener %s for address: %s"), *Object->GetName(), *Address);
	}
}

TArray<UObject*> USCOSCServerManager::GetAllListenersOfAddress(const FString& Address) const
{
	if (const TArray<UObject*>* Listeners = OSCListeners.Find(Address))
	{
		return *Listeners;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No listener registered to address: %s"), *Address);
		return TArray<UObject*>();
	}
}

void USCOSCServerManager::UnregisterAllListenersOfAddress(const FString& Address)
{
	if (OSCListeners.Contains(Address))
	{
		OSCListeners.Remove(Address);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No listener to unregister for address: %s"), *Address);
	}
}
