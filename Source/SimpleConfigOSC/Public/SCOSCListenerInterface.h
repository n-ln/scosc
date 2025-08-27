// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCOSCTypes.h"
#include "UObject/Interface.h"
#include "OSCMessage.h"
#include "SCOSCListenerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class USCOSCListenerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLECONFIGOSC_API ISCOSCListenerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	virtual FSCOSCListenerStatus GetOSCListenerStatus() const;

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	virtual void SetOSCListenerStatus(const FSCOSCListenerStatus& NewStatusData);

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	virtual bool RegisterListenAddress(const FName& TargetAddress);

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	virtual void OnOSCMessageReceived(const TArray<UE::OSC::FOSCData>& Payload, const FString& Address, const EOSCDataType DataType);
};
