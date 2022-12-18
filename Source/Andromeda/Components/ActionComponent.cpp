// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "Andromeda/Actions/Action.h"

// Sets default values for this component's properties
UActionComponent::UActionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}

UAction* UActionComponent::AddAction(TSubclassOf<UAction> NewActionClass)
{
	if(!ensure(NewActionClass))
	{
		return nullptr;
	}

	UAction* NewAction = NewObject<UAction>(this, NewActionClass);

	ActionQueue.Add(NewAction);
	StartAction();

	return NewAction;
}


void UActionComponent::StartAction()
{
	if(UAction* Action = ActionQueue[0])
	{
		Action->StartAction(GetOwner());
		Action->ActionFinished.AddDynamic(this, &UActionComponent::ActionStopped);
	}
}

void UActionComponent::ActionStopped(UAction* Action)
{
	Action->ActionFinished.RemoveDynamic(this, &UActionComponent::ActionStopped);
	StartAction(); //Start another queued action
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();
}



