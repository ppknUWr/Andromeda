// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEquipAction.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Items/WeaponItem.h"


UWeaponEquipAction::UWeaponEquipAction()
{
}


void UWeaponEquipAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	
	UAnimInstance * AnimInstance = ModularCharacter->GetMesh()->GetAnimInstance();

	if(!ModularCharacter || !AnimInstance || !WeaponComponent || !WeaponComponent->WeaponItem)
	{
		StopAction(Instigator);
		return;
	}

	if(UAnimMontage* EquipMontage =  WeaponComponent->WeaponItem->EquipMontage)
	{

		AnimInstance->Montage_Play(EquipMontage);
		
		MontageBlendingOutStarted.BindUObject(this, &UWeaponEquipAction::FinishedMontageInternal);
		
		AnimInstance->Montage_SetBlendingOutDelegate(MontageBlendingOutStarted, EquipMontage);
	}
}