// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "WeaponAttackAction.generated.h"

/**
 * 
 */

class AModularCharacter;

UCLASS()
class ANDROMEDA_API UWeaponAttackAction : public UAction
{

	GENERATED_BODY()
	
public:

	UWeaponAttackAction();
	
    virtual void StartAction_Implementation(AActor* Instigator) override;

private:
	UFUNCTION()
	void FinishedMontageInternal(UAnimMontage* AnimMontage, bool bInterrupted);
};
