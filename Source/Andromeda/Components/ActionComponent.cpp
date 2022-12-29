// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "Andromeda/Andromeda.h"
#include "Andromeda/Actions/Action.h"


UActionComponent::UActionComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

UAction* UActionComponent::AddAction(TSubclassOf<UAction> NewActionClass, bool bInterruptCurrentAction)
{
	if(!ensure(NewActionClass))
	{
		return nullptr;
	}

	UAction* NewAction = NewObject<UAction>(GetOwner(), NewActionClass);

	if(!NewAction)
	{
		return nullptr;
	}

	if(CurrentAction == nullptr || (CurrentAction->bCanBeInterrupted && bInterruptCurrentAction))
	{
		CurrentAction = NewAction;
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
		CurrentAction->StartAction(GetOwner());
		PrintInfo("ActionStarted " + CurrentAction->GetName());
		CurrentAction->ActionFinished.AddDynamic(this, &UActionComponent::ActionStopped);
	}
}

void UActionComponent::ActionStopped()
{
	CurrentAction->ActionFinished.RemoveDynamic(this, &UActionComponent::ActionStopped);
	
	CurrentAction = QueuedAction;
	QueuedAction = nullptr;
	
	StartAction(); //Start another queued action
}

