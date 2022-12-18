// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAction.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Items/WeaponItem.h"


void UAttackAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ModularCharacter = Cast<AModularCharacter>(Instigator);

	if(ModularCharacter && ModularCharacter->RightHandWeapon->WeaponItem)
	{
		ModularCharacter->RightHandWeapon->WeaponItem->MouseButtonPressed(ModularCharacter, true);
		ModularCharacter->GetMesh()->GetAnimInstance()->GetActiveMontageInstance()->OnMontageEnded.BindUFunction(this, "StopAction");
	}
}

void UAttackAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	
}
