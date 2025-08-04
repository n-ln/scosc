// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCManagerSubsystem.h"

#include "OSCServer.h"
#include "OSCClient.h"
#include "OSCMessage.h"
#include "OSCManager.h"

void USCOSCManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
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
	OSCServer->OnOscMessageReceived.AddDynamic(this, &USCOSCManagerSubsystem::HandleReceivedMessage);

	// Create OSC Client
	// TODO Multi client support
	OSCClients.Add(FName("OSCClient"), CreateClient(FName("OSCClient"), TargetAddress, TargetPort));

	UE_LOG(LogTemp, Warning, TEXT("OSC Manager Subsystem initialized"));

}

void USCOSCManagerSubsystem::Deinitialize()
{
	StopServer();
	// Destroy all OSC Clients
	for (const TPair<FName, UOSCClient*>& ClientPair : OSCClients)
	{
		if (ClientPair.Value)
		{
			DestroyClient(ClientPair.Key);
		}
	}

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

void USCOSCManagerSubsystem::SetServerPort(const uint16 Port)
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

UOSCClient* USCOSCManagerSubsystem::CreateClient(const FName ClientName, const FString& IPAddress, const uint16 Port)
{
	UE_LOG(LogTemp, Warning, TEXT("Creating OSC Client: %s at %s:%d"), *ClientName.ToString(), *IPAddress, Port);

	//Create OSC Client
	UOSCClient* NewOSCClient = NewObject<UOSCClient>(this, ClientName);
	NewOSCClient->Connect();
	NewOSCClient->SetSendIPAddress(IPAddress, Port);

	if (!NewOSCClient->IsActive())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create OSC Client: %s at %s:%d"), *ClientName.ToString(), *IPAddress, Port);
		return nullptr;
	}

	return NewOSCClient;
}

void USCOSCManagerSubsystem::DestroyClient(const FName ClientName)
{
	UE_LOG(LogTemp, Warning, TEXT("Destroying OSC Client: %s"), *ClientName.ToString());

	UOSCClient* Client = OSCClients.FindRef(ClientName);
	if (!Client)
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Client %s not found"), *ClientName.ToString());
		return;
	}

	// TODO: Need to destroy the client?
}

void USCOSCManagerSubsystem::SetClientDestination(const FName ClientName, const FString& IPAddress, const uint16 Port)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting OSC Client %s destination to %s:%d"), *ClientName.ToString(), *IPAddress, Port);

	UOSCClient* Client = OSCClients.FindRef(ClientName);
	if (!Client)
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Client %s not found"), *ClientName.ToString());
		return;
	}

	if (!Client->SetSendIPAddress(IPAddress, Port))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to set OSC Client %s destination to %s:%d"), *ClientName.ToString(), *IPAddress, Port);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("OSC Client %s destination set to %s:%d"), *ClientName.ToString(), *IPAddress, Port);
}

void USCOSCManagerSubsystem::SendOSCMessage(const FName ClientName, const FString& Address, const TArray<float>& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("Sending OSC Message from Client: %s"), *ClientName.ToString());

	UOSCClient* Client = OSCClients.FindRef(ClientName);
	if (!Client)
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Client %s not found"), *ClientName.ToString());
		return;
	}

	FOSCMessage OSCMessage;
	OSCMessage.SetAddress(FOSCAddress(Address));

	for (const float& Value : Message)
	{
		UOSCManager::AddFloat(OSCMessage, Value);
	}

	Client->SendOSCMessage(OSCMessage);
	UE_LOG(LogTemp, Warning, TEXT("OSC Message sent from Client: %s"), *ClientName.ToString());
	
}

