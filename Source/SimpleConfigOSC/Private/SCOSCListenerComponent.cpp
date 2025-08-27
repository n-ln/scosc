// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCListenerComponent.h"
#include "SCOSCServerManager.h"


// Sets default values for this component's properties
USCOSCListenerComponent::USCOSCListenerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USCOSCListenerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// Get the current world context
	if (UWorld* World = GetWorld())
	{
		ServerManager = World->GetGameInstance()->GetSubsystem<USCOSCServerManager>();
		if (ServerManager)
		{
			// Temp: Register this component as a universal listener
			TArray<FString> Addresses = {TEXT("*")};
			ServerManager->RegisterListener(this, Addresses);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("SCOSCListenerComponent: Unable to get ServerManager"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SCOSCListenerComponent: Unable to get World context") );
	}
	
}

void USCOSCListenerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Unregister from server manager before destruction
	if (ServerManager)
	{
		TArray<FString> Addresses = {TEXT("*")};
		ServerManager->UnregisterListener(this, Addresses);
	}
	
	Super::EndPlay(EndPlayReason);
}

/*
// Called every frame
void USCOSCListenerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/

// ISCOSCListenerInterface implementation
FSCOSCListenerStatus USCOSCListenerComponent::GetOSCListenerStatus() const
{
	// Placeholder
	return ListenerStatus;
}

void USCOSCListenerComponent::SetOSCListenerStatus(const FSCOSCListenerStatus& NewStatusData)
{
	// Placeholder
	ListenerStatus = NewStatusData;
}

bool USCOSCListenerComponent::RegisterListenAddress(const FName& TargetAddress)
{
	// Placeholder
	return true;
}

void USCOSCListenerComponent::OnOSCMessageReceived(const TArray<UE::OSC::FOSCData>& Payload, const FString& Address, const EOSCDataType Datatype)
{

	// Temp: assume data in floats, parse the message
	TArray<float> FloatData;
	for (const UE::OSC::FOSCData& Item : Payload)
	{
		if (Item.IsFloat())
		{
			FloatData.Add(Item.GetFloat());
		}
	}

	// Call Blueprint event
	OnIncomingOSCFloats.Broadcast(Address, FloatData);
	
	//UE_LOG(LogTemp, Log, TEXT("OSC Message Received at %s - Address: %s, Float values: %d"), 
	//	*GetOwner()->GetName(), *Address, FloatData.Num());
}
