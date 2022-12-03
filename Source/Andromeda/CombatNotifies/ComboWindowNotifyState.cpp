// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboWindowNotifyState.h"

#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Items/SideArmsWeaponItem.h"

#define PrintInfo(String) GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue, String)

void UComboWindowNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ModularCharacter = Cast<AModularCharacter>(MeshComp->GetOwner());
	
	if(ModularCharacter != nullptr)
	{
		WeaponItem = Cast<USideArmsWeaponItem>(ModularCharacter->Weapon->WeaponItem);

		if(!bIsLastAttack)
		{
			ModularCharacter->OnLeftMouseButtonClicked.AddDynamic(this, &UComboWindowNotifyState::PerformCombo);
		}
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
			WeaponItem->AttackWithCombo(ModularCharacter->GetMesh());
		}
		
		if(!bComboTriggered || bIsLastAttack)
		{
			WeaponItem->ComboCounter = 0;
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
