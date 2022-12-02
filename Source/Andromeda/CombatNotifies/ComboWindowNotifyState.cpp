// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboWindowNotifyState.h"

#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Items/WeaponItem.h"

#define PrintInfo(String) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, String)

void UComboWindowNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ModularCharacter = Cast<AModularCharacter>(MeshComp->GetOwner());
	
	if(ModularCharacter != nullptr)
	{
		WeaponItem = ModularCharacter->Weapon->WeaponItem;
		ModularCharacter->OnLeftMouseButtonClicked.AddDynamic(this, &UComboWindowNotifyState::BindCombo);
	}
}

void UComboWindowNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(ModularCharacter)
	{
		ModularCharacter->OnLeftMouseButtonClicked.RemoveDynamic(this,  &UComboWindowNotifyState::BindCombo);
	}
}

void UComboWindowNotifyState::BindCombo(EInputEvent InputEvent)
{
	if(InputEvent == IE_Pressed)
	{
		PrintInfo("FunctionCalled");
		WeaponItem->AttackWithCombo(ModularCharacter->GetMesh());
	}
}
