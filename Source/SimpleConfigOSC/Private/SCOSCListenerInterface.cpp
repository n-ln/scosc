// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCListenerInterface.h"


// Add default functionality here for any ISCOSCListenerInterface functions that are not pure virtual.

FSCOSCListenerStatus ISCOSCListenerInterface::GetOSCListenerStatus() const
{
	return FSCOSCListenerStatus();
}

void ISCOSCListenerInterface::SetOSCListenerStatus(const FSCOSCListenerStatus& NewStatusData)
{
	// Default implementation
}

bool ISCOSCListenerInterface::RegisterListenAddress(const FName& TargetAddress)
{
	return false;
}

void ISCOSCListenerInterface::OnOSCMessageReceived(const TArray<UE::OSC::FOSCData>& Payload, const FString& Address, const EOSCDataType DataType)
{
	// Default implementation
}
