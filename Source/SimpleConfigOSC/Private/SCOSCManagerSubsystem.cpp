// Fill out your copyright notice in the Description page of Project Settings.


#include "SCOSCManagerSubsystem.h"


void USCOSCManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//TODO: Should add auto start logic?
}

void USCOSCManagerSubsystem::Deinitialize()
{
	//TODO: Stop OSC server&client
	
	Super::Deinitialize();
}

