// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/WeaponComponent.h"

#define PrintInfo(String) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, String)

void UWeaponItem::Use(AModularCharacter* Character)
{
	Super::Use(Character);

	Character->Weapon->ChangeWeapon(this);
}

void UWeaponItem::LeftMousePressed_Implementation(AModularCharacter* ModularCharacter)
{
}
