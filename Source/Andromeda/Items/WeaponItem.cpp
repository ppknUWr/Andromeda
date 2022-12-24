// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Components/ActionComponent.h"
#include "Andromeda/Components/WeaponComponent.h"

#define PrintInfo(String) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, String)

void UWeaponItem::Use(AModularCharacter* Character)
{
	Super::Use(Character);

	switch (PreferableHand)
	{
	case RightHand:
		Character->RightHandWeapon->ChangeWeapon(this);
		break;
	case LeftHand:
		Character->LeftHandWeapon->ChangeWeapon(this);
		break;
	case BothHands:
		if(bIsTwoHandedWeaponForRightHand)
		{
			Character->RightHandWeapon->ChangeWeapon(this);
			Character->LeftHandWeapon->WeaponItem = this; //make it possible for input being called with other button
		}
		else
		{
			Character->LeftHandWeapon->ChangeWeapon(this);
			Character->RightHandWeapon->WeaponItem = this;
		}
		break;
	default:
		break;
	}

}

void UWeaponItem::MouseButtonPressed_Implementation(AModularCharacter* ModularCharacter, bool bIsRightHand)
{
}

void UWeaponItem::MouseButtonReleased_Implementation(AModularCharacter* ModularCharacter, bool bIsRightHand)
{
}