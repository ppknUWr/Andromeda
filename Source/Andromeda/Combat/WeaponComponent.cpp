// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Andromeda/Character/ModularCharacter.h"

#include "Andromeda/Equipment/WeaponItem.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	if(WeaponItem)
	{
		SetSkeletalMesh(WeaponItem->AttachMesh);
	}
}


bool UWeaponComponent::IsWeaponAtRest()
{
	if(!WeaponItem)
		return true;
	
	return GetAttachSocketName() == WeaponItem->WeaponRestSocket;
}

bool UWeaponComponent::IsWeaponEquipped()
{
	if(!WeaponItem)
		return false;
	
	return GetAttachSocketName() == WeaponItem->WeaponAttachSocket;
}

void UWeaponComponent::EquipWeapon(AModularCharacter* ModularCharacter)
{
	ModularCharacter->PlayAnimMontage(WeaponItem->EquipMontage);
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if(WeaponItem)
	{
		SetSkeletalMesh(WeaponItem->AttachMesh);

		if(AModularCharacter* ModularCharacter = Cast<AModularCharacter>(GetOwner()))
		{
			AttachToComponent(ModularCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponItem->WeaponRestSocket);
		}
	}
}
