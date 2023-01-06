// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAction.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/WeaponComponent.h"


UWeaponAction::UWeaponAction()
{
}

void UWeaponAction::SetAdditionalParams_Implementation(const TMap<FName, UObject*>& AdditionalObjects)
{
	WeaponComponent = Cast<UWeaponComponent>(AdditionalObjects["WeaponComponent"]);
}

void UWeaponAction::FinishedMontageInternal(UAnimMontage* AnimMontage, bool bInterrupted)
{
	StopAction(ModularCharacter);
}
