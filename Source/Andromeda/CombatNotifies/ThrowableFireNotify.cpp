// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableFireNotify.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Items/ThrowableWeaponItem.h"
#include "Engine/World.h"
#include "Andromeda/Throwable/ThrowableActor.h"
#include "Camera/CameraComponent.h"


UThrowableFireNotify::UThrowableFireNotify()
{
	
}

void UThrowableFireNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

	Super::Notify(MeshComp, Animation, EventReference);

	if (SpawnFireActorBP && MeshComp->GetWorld()) 
	{
		if (AModularCharacter* ModularCharacter = MeshComp->GetOwner<AModularCharacter>())
		{
			const FVector LocationFire =  ModularCharacter->RightHandWeapon->GetSocketLocation("ArrowSocket");
			const FRotator RotationFire = ModularCharacter->GetActorRotation();
			
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = ModularCharacter;
			SpawnParameters.Instigator = ModularCharacter->GetInstigator();
			
			UThrowableWeaponItem* ThrowableItem = Cast<UThrowableWeaponItem>(ModularCharacter->RightHandWeapon->WeaponItem);
			//Actual Spawn. The following function returns a reference to the spawned actor
			AThrowableActor* SpawnFireActorRef = MeshComp->GetWorld()->SpawnActor<AThrowableActor>(SpawnFireActorBP, LocationFire, RotationFire, SpawnParameters);
			
			SpawnFireActorRef->ChangeItem(ThrowableItem->SpawnWeaponClass);

			ModularCharacter->SpawnThrowableActor = SpawnFireActorRef;
			FAttachmentTransformRules AttachRule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
			SpawnFireActorRef->AttachToComponent(ModularCharacter->RightHandWeapon, AttachRule, "ArrowSocket");
			
		}
	}
}


