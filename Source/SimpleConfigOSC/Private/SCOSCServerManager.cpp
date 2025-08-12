// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCServerManager.h"

#include "OSCServer.h"
#include "OSCMessage.h"
#include "OSCManager.h"

void USCOSCServerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ServerSettings = GetMutableDefault<USCOSCServerSettings>();

	// Temp: Add a server config to settings
	FSCOSCServerConfig TempConfig(FString("0.0.0.0"), 38000, true);
	ServerSettings->ServerParameters.ServerConfigs.FindOrAdd(FName("DefaultServer")) = TempConfig;
	

	// Initialize servers from settings
	for (const TPair<FName, FSCOSCServerConfig>& Config : ServerSettings->ServerParameters.ServerConfigs)
	{
		if (OSCServers.Contains(Config.Key))
		{
			UE_LOG(LogTemp, Error, TEXT("OSC Server %s already exists"), *Config.Key.ToString());
			continue;
		}

		UOSCServer* NewServer = CreateServer(Config.Key);
		if (!NewServer)
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot create OSC Server %s"), *Config.Key.ToString());
			continue;
		}
		FSCOSCServerRuntimeStatus NewServerStatus(NewServer, false);
		OSCServers.Add(Config.Key, NewServerStatus);

		SetServerEndpoint(Config.Key, Config.Value.IPAddress, Config.Value.Port);

		if (Config.Value.bEnableByDefault)
		{
			StartServer(Config.Key);
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("OSC Server Manager initialized"));
}

void USCOSCServerManager::Deinitialize()
{
	// Stop all servers
	for (TPair<FName, FSCOSCServerRuntimeStatus> Server : OSCServers)
	{
		StopServer(Server.Key);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("OSC Server Manager deinitialized"));
	
	Super::Deinitialize();
}

UOSCServer* USCOSCServerManager::CreateServer(FName ServerName)
{
	UE_LOG(LogTemp, Warning, TEXT("Creating OSC Server: %s"), *ServerName.ToString());
	UOSCServer* NewOSCServer = NewObject<UOSCServer>(this, ServerName);

	// Bind to OnOscMessageReceived
	NewOSCServer->OnOscMessageReceived.AddDynamic(this, &USCOSCServerManager::HandleReceivedMessage);
	
	return NewOSCServer;
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
		UE_LOG(LogTemp, Error, TEXT("OSC Server %s is already started"), *ServerName.ToString());
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
		UE_LOG(LogTemp, Error, TEXT("OSC Server %s is already stopped"), *ServerName.ToString());
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
}

void USCOSCServerManager::ToggleServerMain(bool bEnable)
{
	if (bEnable)
	{
		// Start all servers
		for (TPair<FName, FSCOSCServerRuntimeStatus> Server : OSCServers)
		{
			StartServer(Server.Key);
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
