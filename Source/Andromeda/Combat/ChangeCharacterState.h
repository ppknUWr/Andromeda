// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Andromeda/Character/CharacterStats.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ChangeCharacterState.generated.h"

/**
 * 
 */
UCLASS()
class ANDROMEDA_API UChangeCharacterState : public UAnimNotify
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	ECharacterState DestinedCharacterState;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};
