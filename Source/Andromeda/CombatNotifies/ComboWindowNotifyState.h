﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ComboWindowNotifyState.generated.h"

class AModularCharacter;

/**
 * 
 */
UCLASS()
class ANDROMEDA_API UComboWindowNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY()
	AModularCharacter* ModularCharacter;
	
	UPROPERTY(EditAnywhere)
	bool bIsLastAttack = false;

	UPROPERTY()
	bool bComboTriggered = false;
	
	UFUNCTION()
	void PerformCombo(EInputEvent InputEvent);
	
};
