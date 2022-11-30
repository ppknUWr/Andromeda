// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EquipWeaponNotify.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANDROMEDA_API UEquipWeaponNotify : public UAnimNotify
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipWeaponNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, DisplayName = "Should Equip?")
	bool bShouldEquip = true;

};
