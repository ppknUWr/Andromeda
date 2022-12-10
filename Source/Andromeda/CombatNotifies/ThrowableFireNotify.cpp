// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableFireNotify.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Items/WeaponItem.h"
#include "Engine/World.h"
#include "Andromeda/Throwable/ThrowableActor.h"


UThrowableFireNotify::UThrowableFireNotify()
{
	
}

void UThrowableFireNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

	Super::Notify(MeshComp, Animation, EventReference);

	if (SpawnFireActorBP && MeshComp->GetWorld()) 
	{
		LocationFire =  MeshComp->GetSocketLocation("RightHandSocket");

		RotationFire = MeshComp->GetOwner()->GetActorRotation();

		//Actual Spawn. The following function returns a reference to the spawned actor
		AThrowableActor* SpawnFireActorRef = MeshComp->GetWorld()->SpawnActor<AThrowableActor>(SpawnFireActorBP, LocationFire, RotationFire);
	
		ModularCharacter = MeshComp->GetOwner<AModularCharacter>();
		if (ModularCharacter)
		{
			ModularCharacter->SpawnThrowableActor = SpawnFireActorRef;
			SpawnFireActorRef->AttachToComponent(ModularCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "RightHandSocket");
		}
	}
}


