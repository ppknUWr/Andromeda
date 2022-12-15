// Fill out your copyright notice in the Description page of Project Settings.


#include "SideArmsWeaponItem.h"
#include "Andromeda/Character/ModularCharacter.h"

void USideArmsWeaponItem::MouseButtonPressed_Implementation(AModularCharacter* ModularCharacter, bool bIsRightHand)
{
	AttackWithCombo(ModularCharacter->GetMesh(), 0);
}

void USideArmsWeaponItem::AttackWithCombo(USkeletalMeshComponent* MeshComponent, int32 ComboIndex) const
{
	//copied & modified from ACharacter::PlayAnimMontage -> we want to change sections in current montage, not to play another
	UAnimInstance * AnimInstance = (MeshComponent)? MeshComponent->GetAnimInstance() : nullptr; 
	if( AttackMontage && AnimInstance )
	{
		if(ComboIndex == 0)
		{
			AnimInstance->Montage_Play(AttackMontage, 1);
		}
		else
		{
			const FName SectionName = AttackMontage->GetSectionName(ComboIndex);
			
			AnimInstance->Montage_JumpToSection(SectionName, AttackMontage); 
		}
	}
}
