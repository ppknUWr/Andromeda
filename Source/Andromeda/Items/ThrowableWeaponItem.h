// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponItem.h"
#include "Andromeda/Character/CharacterStats.h"
#include "ThrowableWeaponItem.generated.h"

/**
 * 
 */

UCLASS()
class ANDROMEDA_API UThrowableWeaponItem : public UWeaponItem
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWeaponItem> SpawnWeaponClass;
};
