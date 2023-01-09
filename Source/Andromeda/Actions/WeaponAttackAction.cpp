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
	
	UAnimInstance * AnimInstance = ModularCharacter->GetMesh()->GetAnimInstance();

	if(!ModularCharacter || !AnimInstance || !WeaponComponent)
	{
		return;
	}
	
	if(UAnimMontage* AttackMontage =  WeaponComponent->WeaponItem->AttackMontage)
	{
		if(ModularCharacter->ComboCounter == 0)
		{
			AnimInstance->Montage_Play(AttackMontage);
		}
		else
		{
			const FName SectionName = AttackMontage->GetSectionName(ModularCharacter->ComboCounter % AttackMontage->CompositeSections.Num());

			AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
		}
		
		MontageBlendingOutStarted.BindUObject(this, &UWeaponAttackAction::FinishedMontageInternal);
		
		AnimInstance->Montage_SetBlendingOutDelegate(MontageBlendingOutStarted, AttackMontage);
	}
	
}