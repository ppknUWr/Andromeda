// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponAttackAction.h"
#include "WeaponBlockAction.generated.h"

/**
 * 
 */
UCLASS()
class ANDROMEDA_API UWeaponBlockAction : public UWeaponAction
{
	GENERATED_BODY()

public:
	UWeaponBlockAction();

	virtual void StartAction_Implementation(AActor* Instigator) override;
	
};
