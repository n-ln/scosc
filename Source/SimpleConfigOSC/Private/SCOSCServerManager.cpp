// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCServerManager.h"

#include "OSCServer.h"
#include "OSCManager.h"
#include "SCOSCListenerInterface.h"

void USCOSCServerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ServerSettings = GetMutableDefault<USCOSCServerSettings>();

	// Initialize servers from settings
	for (const TPair<FName, FSCOSCServerConfig>& Config : ServerSettings->ServerParameters.ServerConfigs)
	{
		if (CreateServer(Config.Key))
		{
			SetServerEndpoint(Config.Key, Config.Value.IPAddress, Config.Value.Port);
		}
	}

	// Start enabled server if main toggle is enabled
	ToggleServerMain(ServerSettings->ServerParameters.bEnableServerMain);
	
	UE_LOG(LogTemp, Warning, TEXT("OSC Server Manager initialized"));
}

void USCOSCServerManager::Deinitialize()
{
	// Stop all servers
	for (TPair<FName, FSCOSCServerRuntimeStatus> Server : OSCServers)
	{
		if (Server.Value.OSCServer->IsActive())
		{
			StopServer(Server.Key);
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("OSC Server Manager deinitialized"));
	
	Super::Deinitialize();
}

bool USCOSCServerManager::CreateServer(FName ServerName)
{
	if (OSCServers.Contains(ServerName))
	{
		UE_LOG(LogTemp, Error, TEXT("OSC Server %s already exists"), *ServerName.ToString());
		return false;
	}
	
	UOSCServer* NewOSCServer = NewObject<UOSCServer>(this, ServerName);

	if (!NewOSCServer)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot create OSC Server %s"), *ServerName.ToString());
		return false;
	}

	// Bind to OnOscMessageReceived
	NewOSCServer->OnOscMessageReceived.AddDynamic(this, &USCOSCServerManager::HandleReceivedMessage);

	FSCOSCServerRuntimeStatus NewServerStatus(NewOSCServer, false);
	OSCServers.Add(ServerName, NewServerStatus);

	UE_LOG(LogTemp, Warning, TEXT("Created OSC Server: %s"), *ServerName.ToString());
	return true;
}

UOSCServer* USCOSCServerManager::GetOSCServer(FName ServerName) const
{
	return OSCServers.FindRef(ServerName).OSCServer;
}

void USCOSCServerManager::StartServer(FName ServerName)
{
	FSCOSCServerRuntimeStatus* Server = OSCServers.Find(ServerName);
	if (!Server)
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Server %s not found"), *ServerName.ToString());
		return;
	}
	if (Server->OSCServer->IsActive())
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Server %s is already started"), *ServerName.ToString());
		Server->bIsListening = true;
		return;
	}
	Server->OSCServer->Listen();
	if (!Server->OSCServer->IsActive())
	{
		UE_LOG(LogTemp, Error, TEXT("OSC Server %s failed to start"), *ServerName.ToString());
		return;
	}
	Server->bIsListening = true;
	const FSCOSCServerConfig Config = ServerSettings->ServerParameters.ServerConfigs.FindRef(ServerName);
	UE_LOG(LogTemp, Warning, TEXT("OSC Server %s started on %s:%d"), *ServerName.ToString(), *Config.IPAddress, Config.Port);
}

void USCOSCServerManager::StopServer(FName ServerName)
{
	FSCOSCServerRuntimeStatus* Server = OSCServers.Find(ServerName);
	if (!Server)
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Server %s not found"), *ServerName.ToString());
		return;
	}
	if (!Server->OSCServer->IsActive())
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Server %s is already stopped"), *ServerName.ToString());
		Server->bIsListening = false;
		return;
	}
	Server->OSCServer->Stop();
	if (Server->OSCServer->IsActive())
	{
		UE_LOG(LogTemp, Error, TEXT("OSC Server %s failed to stop"), *ServerName.ToString());
		return;
	}
	Server->bIsListening = false;
	UE_LOG(LogTemp, Warning, TEXT("OSC Server %s stopped"), *ServerName.ToString());
}

void USCOSCServerManager::SetServerEndpoint(FName ServerName, const FString& Address, uint16 Port)
{
	FSCOSCServerRuntimeStatus* Server = OSCServers.Find(ServerName);
	if (!Server)
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Server %s not found"), *ServerName.ToString());
		return;
	}
	Server->OSCServer->SetAddress(Address, Port);
	if (Server->OSCServer->GetIpAddress(false) == Address && Server->OSCServer->GetPort() == Port)
	{
		UE_LOG(LogTemp, Warning, TEXT("OSC Server %s endpoint set to %s:%d"), *ServerName.ToString(), *Address, Port);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set OSC Server %s endpoint"), *ServerName.ToString());
	}
}

void USCOSCServerManager::HandleReceivedMessage(const FOSCMessage& Message, const FString& IPAddress, const int32 Port)
{
	UE_LOG(LogTemp, Warning, TEXT("Received OSC Message: %s from %s:%d"), *Message.GetAddress().GetFullPath(), *IPAddress, Port);

	// Get OSC address and data
	const FString& Address = Message.GetAddress().GetFullPath();
	const TArray<UE::OSC::FOSCData>& Payload = Message.GetArgumentsChecked();
	
	// Test: don't check OSC address, broadcast to all listeners (*)
	if (const TArray<UObject*>* Listeners = OSCListeners.Find(TEXT("*")))
	//if (const TArray<UObject*>* Listeners = OSCListeners.Find(Address))
	{
		for (UObject* ListenerObject : *Listeners)
		{
			if (IsValid(ListenerObject))
			{
				// Cast to interface and call OnOSCMessageReceived
				if (ISCOSCListenerInterface* ListenerInterface = Cast<ISCOSCListenerInterface>(ListenerObject))
				{
					ListenerInterface->OnOSCMessageReceived(Payload, Address, EOSCDataType::Float32);
				}
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Broadcasted OSC message to listener %d"),
			Listeners->Num());
	}
}

void USCOSCServerManager::ToggleServerMain(bool bEnable)
{
	if (bEnable)
	{
		// Start server if set to enabled in settings
		for (TPair<FName, FSCOSCServerRuntimeStatus> Server : OSCServers)
		{
			FSCOSCServerConfig Config = ServerSettings->ServerParameters.ServerConfigs.FindRef(Server.Key);
			if (Config.bIsEnabled)
			{
				StartServer(Server.Key);
			}
			else
			{
				StopServer(Server.Key);
			}
		}
	}
	else
	{
		// Stop all servers
		for (TPair<FName, FSCOSCServerRuntimeStatus> Server : OSCServers)
		{
			StopServer(Server.Key);
		}
	}
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
