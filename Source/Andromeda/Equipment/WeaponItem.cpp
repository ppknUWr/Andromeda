// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Combat/WeaponComponent.h"

void UWeaponItem::Use(AModularCharacter* Character)
{
	Super::Use(Character);

	Character->Weapon->ChangeWeapon(this);
}
