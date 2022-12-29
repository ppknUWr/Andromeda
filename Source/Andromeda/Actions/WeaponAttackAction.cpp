// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttackAction.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Items/WeaponItem.h"


UWeaponAttackAction::UWeaponAttackAction()
{
}

void UWeaponAttackAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if(!ModularCharacter)
	{
		return;
	}


	if(!ModularCharacter->RightHandWeapon->IsWeaponEquipped())
	{
		ModularCharacter->RightHandWeapon->PlayEquipAnimation(ModularCharacter);
	}
	else
	{
		ModularCharacter->RightHandWeapon->WeaponItem->MouseButtonPressed(ModularCharacter, true);
	}
	
	//PrintInfo(ModularCharacter->GetMesh()->GetAnimInstance()->GetCurrentActiveMontage()->GetName());
	ModularCharacter->GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &UWeaponAttackAction::FinishedMontageInternal);
	
}

void UWeaponAttackAction::FinishedMontageInternal(UAnimMontage* AnimMontage, bool bInterrupted)
{
	StopAction(ModularCharacter);
}
