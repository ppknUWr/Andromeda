// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboWindowNotifyState.h"
#include "Andromeda/Actions/WeaponAttackAction.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/ActionComponent.h"
#include "Andromeda/Components/WeaponComponent.h"


void UComboWindowNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ModularCharacter = Cast<AModularCharacter>(MeshComp->GetOwner());
	bComboTriggered = false;
	
	if(ModularCharacter && !bIsLastAttack)
	{
		ModularCharacter->OnLeftMouseButtonClicked.AddDynamic(this, &UComboWindowNotifyState::PerformCombo);
	}
}

void UComboWindowNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(ModularCharacter)
	{
		ModularCharacter->OnLeftMouseButtonClicked.RemoveDynamic(this,  &UComboWindowNotifyState::PerformCombo);

		if(bComboTriggered)
		{
			ModularCharacter->ComboCounter++;
			ModularCharacter->ActionComponent->AddAction(UWeaponAttackAction::StaticClass(), {{"WeaponComponent", ModularCharacter->RightHandWeapon}}, true);
		}
		
		if(!bComboTriggered || bIsLastAttack)
		{
			ModularCharacter->ComboCounter = 0;
		}
	}
}

void UComboWindowNotifyState::PerformCombo(EInputEvent InputEvent)
{
	if(InputEvent == IE_Pressed)
	{
		bComboTriggered = true;
	}
}
