// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "Andromeda/Character/ModularCharacter.h"

UAction::UAction()
{
	
}

void UAction::StartAction_Implementation(AActor* Instigator)
{
	ModularCharacter = Cast<AModularCharacter>(Instigator);
	ActionStarted.Broadcast(this);
}

void UAction::OnKeyReleased_Implementation(FKey Key)
{
	
}

void UAction::OnKeyPressed_Implementation(FKey Key)
{
	
}

void UAction::StopAction_Implementation(AActor* Instigator)
{
	ActionFinished.Broadcast();
}


