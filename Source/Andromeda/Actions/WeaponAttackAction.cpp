// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttackAction.h"

#include "Andromeda/Andromeda.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Items/WeaponItem.h"


void USidearmsAttackAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if(!ModularCharacter)
	{
		return;
	}

	if(ModularCharacter->GetLocalViewingPlayerController()->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		if(ModularCharacter->RightHandWeapon->IsWeaponEquipped())
		{
			ModularCharacter->RightHandWeapon->WeaponItem->MouseButtonPressed(ModularCharacter, true);
		}
		else
		{
			ModularCharacter->RightHandWeapon->PlayEquipAnimation(ModularCharacter);
		}
		PrintInfo(ModularCharacter->GetMesh()->GetAnimInstance()->GetCurrentActiveMontage()->GetName());
		ModularCharacter->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &USidearmsAttackAction::FinishedMontageInternal);
	}
}

void USidearmsAttackAction::FinishedMontageInternal(UAnimMontage* AnimMontage, bool bInterrupted)
{
	StopAction(ModularCharacter);
	PrintInfo("Montage Ended");
}
