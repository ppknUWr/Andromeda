// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "SidearmsAttackAction.generated.h"

/**
 * 
 */

class AModularCharacter;

UCLASS()
class ANDROMEDA_API USidearmsAttackAction : public UAction
{

	GENERATED_BODY()
	
public:
    virtual void StartAction_Implementation(AActor* Instigator) override;
    virtual void StopAction_Implementation(AActor* Instigator) override;
	
};
