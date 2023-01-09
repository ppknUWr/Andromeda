// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "Andromeda/Actions/Action.h"
#include "Andromeda/Actions/WeaponEquipAction.h"


UActionComponent::UActionComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

UAction* UActionComponent::AddAction(TSubclassOf<UAction> NewActionClass, TMap<FName, UObject*> AdditionalObjects, bool bForceInterrupt)
{
	if(!ensure(NewActionClass))
	{
		return nullptr;
	}

	UAction* NewAction = NewObject<UAction>(GetOwner(), NewActionClass);
	NewAction->SetAdditionalParams(AdditionalObjects);

	if(CurrentAction == nullptr || NewAction->bCanInterruptAction || (bForceInterrupt && !Cast<UWeaponEquipAction>(CurrentAction)))
	{
		CurrentAction = NewAction;
		QueuedAction = nullptr;
		StartAction();
	}
	else
	{
		QueuedAction = NewAction;
	}
	
	return NewAction;
}


void UActionComponent::StartAction()
{
	if(CurrentAction)
	{
		CurrentAction->ActionFinished.AddDynamic(this, &UActionComponent::ActionStopped);
		CurrentAction->StartAction(GetOwner());
	}
}

void UActionComponent::ActionStopped()
{
	CurrentAction->ActionFinished.RemoveDynamic(this, &UActionComponent::ActionStopped);
	
	CurrentAction = QueuedAction;
	QueuedAction = nullptr;
	
	StartAction(); //Start another queued action
}

