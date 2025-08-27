// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCOSCTypes.h"
#include "OSCMessage.h"
#include "SCOSCListenerInterface.h"
#include "SCOSCListenerComponent.generated.h"


class USCOSCServerManager;
class UE::OSC::FOSCData;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLECONFIGOSC_API USCOSCListenerComponent : public UActorComponent, public ISCOSCListenerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USCOSCListenerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Server manager instance
	UPROPERTY()
	USCOSCServerManager* ServerManager;

	// Current listener status
	UPROPERTY()
	FSCOSCListenerStatus ListenerStatus;

public:
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	//                           FActorComponentTickFunction* ThisTickFunction) override;

	// Begin ISCOSCListenerInterface implementation
	UFUNCTION(BlueprintCallable)
	virtual FSCOSCListenerStatus GetOSCListenerStatus() const override;
	UFUNCTION(BlueprintCallable)
	virtual void SetOSCListenerStatus(const FSCOSCListenerStatus& NewStatusData) override;
	UFUNCTION(BlueprintCallable)
	virtual bool RegisterListenAddress(const FName& TargetAddress) override;
	virtual void OnOSCMessageReceived(const TArray<UE::OSC::FOSCData>& Payload, const FString& Address, const EOSCDataType DataType) override;
	// End ISCOSCListenerInterface implementation
	
	// Access point in Blueprint
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIncomingOSCFloats, const FString&, Address, const TArray<float>&, OSCFloatData);
	UPROPERTY(BlueprintAssignable)
	FOnIncomingOSCFloats OnIncomingOSCFloats;
	/*
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIncomingOSCIntegers, const FString&, Address, const TArray<int32>&, OSCIntegerData);
	UPROPERTY(BlueprintAssignable)
	FOnIncomingOSCIntegers OnIncomingOSCIntegers;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIncomingOSCStrings, const FString&, Address, const TArray<FString>&, OSCStringData);
	UPROPERTY(BlueprintAssignable)
	FOnIncomingOSCStrings OnIncomingOSCStrings;
	*/
};
