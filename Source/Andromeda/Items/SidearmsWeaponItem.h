// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponItem.h"
#include "SidearmsWeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class ANDROMEDA_API USidearmsWeaponItem : public UWeaponItem
{
	GENERATED_BODY()

public:

	virtual void ButtonPressed_Implementation(AModularCharacter* ModularCharacter, FKey PressedKey) override;
	
};
