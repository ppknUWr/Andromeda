// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"

UAction::UAction()
{
	
}

void UAction::StartAction_Implementation(AActor* Instigator)
{
	ActionStarted.Broadcast(this);
}

void UAction::StopAction_Implementation(AActor* Instigator)
{
	ActionFinished.Broadcast(this);
}


