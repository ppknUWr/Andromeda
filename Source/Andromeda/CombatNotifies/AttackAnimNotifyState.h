// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackAnimNotifyState.generated.h"

/**
 * 
 */

class UWeaponComponent;
UCLASS()
class ANDROMEDA_API UAttackAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
	UPROPERTY()
	TArray<AActor*> IgnoreActors;


	TArray<USkeletalMeshSocket*> TraceSockets;
	
	UPROPERTY()
	TArray<FVector> PreviousLocations;

	UPROPERTY()
	UWeaponComponent* Weapon;

	
};
