// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/WeaponComponent.h"

#define PrintInfo(String) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, String)

void UWeaponItem::Use(AModularCharacter* Character)
{
	Super::Use(Character);

	Character->LeftHandWeapon->ChangeWeapon(this);
}

void UWeaponItem::MouseButtonReleased_Implementation(AModularCharacter* ModularCharacter, bool bIsRightHand)
{
}

void UWeaponItem::MouseButtonPressed_Implementation(AModularCharacter* ModularCharacter, bool bIsRightHand)
{
}
