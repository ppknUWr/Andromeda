// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponAction.h"
#include "Animation/AnimMontage.h"
#include "WeaponAttackAction.generated.h"

/**
 * 
 */

class AModularCharacter;
class UWeaponComponent;

UCLASS()
class ANDROMEDA_API UWeaponAttackAction : public UWeaponAction
{

	GENERATED_BODY()
	
public:

	UWeaponAttackAction();
	
    virtual void StartAction_Implementation(AActor* Instigator) override;
	
};
