﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipWeaponNotify.h"
#include "WeaponComponent.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Equipment/WeaponItem.h"


UEquipWeaponNotify::UEquipWeaponNotify()
{

}

void UEquipWeaponNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AModularCharacter* ModularCharacter = Cast<AModularCharacter>(MeshComp->GetOwner()))
	{
		UWeaponItem* WeaponItem = ModularCharacter->Weapon->WeaponItem;
		FName AttachSocket = bShouldEquip ? WeaponItem->WeaponAttachSocket : WeaponItem->WeaponRestSocket;

		ModularCharacter->Weapon->AttachToComponent(ModularCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocket);
	}
}


