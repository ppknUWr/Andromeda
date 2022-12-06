// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableFireNotify.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Items/WeaponItem.h"
#include "Engine/World.h"


UThrowableFireNotify::UThrowableFireNotify()
{
	
}

void UThrowableFireNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	LocationFire =  MeshComp->GetSocketLocation("RightHandSocket");

	RotationFire = MeshComp->GetSocketRotation("head");

	FActorSpawnParameters SpawnParams;

	//Actual Spawn. The following function returns a reference to the spawned actor
	UClass* SpawnFireActorRef = GetWorld()->SpawnActor<UClass>(SpawnFireActorBP, LocationFire, RotationFire, SpawnParams);
}


