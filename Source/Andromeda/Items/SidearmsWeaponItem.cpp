// Fill out your copyright notice in the Description page of Project Settings.


#include "SidearmsWeaponItem.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/ActionComponent.h"
#include "Andromeda/Components/WeaponComponent.h"

void USidearmsWeaponItem::ButtonPressed_Implementation(AModularCharacter* ModularCharacter, FKey PressedKey)
{
	Super::ButtonPressed_Implementation(ModularCharacter, PressedKey);

	ModularCharacter->ActionComponent->AddAction(GetActionByKey(PressedKey), {{"WeaponComponent", WeaponHand}});
}
