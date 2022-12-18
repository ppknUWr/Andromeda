// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "AttackAction.generated.h"

/**
 * 
 */

class AModularCharacter;

UCLASS()
class ANDROMEDA_API UAttackAction : public UAction
{

	GENERATED_BODY()
	
public:
    virtual void StartAction_Implementation(AActor* Instigator) override;
    virtual void StopAction_Implementation(AActor* Instigator) override;

protected:
	UPROPERTY()
	AModularCharacter* ModularCharacter;
};
