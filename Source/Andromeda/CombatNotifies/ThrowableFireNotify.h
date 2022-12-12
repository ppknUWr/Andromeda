// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ThrowableFireNotify.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ANDROMEDA_API UThrowableFireNotify : public UAnimNotify
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UThrowableFireNotify();

	/** Actor **/
	UPROPERTY(EditDefaultsOnly, Category = "SpawnFireActorBP")
		TSubclassOf<AActor> SpawnFireActorBP;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	FVector LocationFire;
	FRotator RotationFire;

};
