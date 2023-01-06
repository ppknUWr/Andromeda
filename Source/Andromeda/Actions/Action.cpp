// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "Andromeda/Character/ModularCharacter.h"

UAction::UAction()
{
	
}

void UAction::StartAction_Implementation(AActor* Instigator)
{
	ModularCharacter = Cast<AModularCharacter>(Instigator);
	ActionStarted.Broadcast();
}

void UAction::StopAction_Implementation(AActor* Instigator)
{
	ActionFinished.Broadcast();
}

void UAction::SetAdditionalParams_Implementation(const TMap<FName, UObject*>& AdditionalObjects)
{
}