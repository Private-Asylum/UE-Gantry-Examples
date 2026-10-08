// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/Level/GTLevelScriptActor.h"

#include "GantryExamplesLogCategories.h"

AGTLevelScriptActor::AGTLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGTLevelScriptActor::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AGTLevelScriptActor::BeginPlay()
{
	UE_LOG(LogGTWorld, Verbose, TEXT("Level script begin play: %s"), *GetName());

	Super::BeginPlay();
}

void AGTLevelScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
