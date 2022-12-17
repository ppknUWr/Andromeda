// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ThrowableFireNotify.generated.h"

class AModularCharacter;
class AThrowableActor;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ANDROMEDA_API UThrowableFireNotify : public UAnimNotify
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UThrowableFireNotify();


	UPROPERTY(EditAnywhere, Category = "SpawnFireActorBP")
	TSubclassOf <AThrowableActor> SpawnFireActorBP;
	

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
