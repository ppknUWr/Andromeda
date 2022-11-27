// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Andromeda/Character/ModularCharacter.h"

#include "Andromeda/Equipment/WeaponItem.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
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

void UWeaponComponent::ChangeWeapon(UWeaponItem* NewWeapon)
{
	if(NewWeapon == WeaponItem || NewWeapon == nullptr)
	{
		return;
	}
	
	if(AModularCharacter* ModularCharacter = Cast<AModularCharacter>(GetOwner()))
	{
		WeaponItem = NewWeapon;
		const FName NewWeaponAttachSocket = IsWeaponEquipped() ? WeaponItem->WeaponAttachSocket : WeaponItem->WeaponRestSocket;
		
		SetSkeletalMesh(WeaponItem->AttachMesh);
		AttachToComponent(ModularCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, NewWeaponAttachSocket);
		//PlayEquipAnimation(ModularCharacter);
	}
	
}

void UWeaponComponent::PlayEquipAnimation(AModularCharacter* ModularCharacter)
{
	if(WeaponItem)
	{
		ModularCharacter->PlayAnimMontage(WeaponItem->EquipMontage);
	}
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
