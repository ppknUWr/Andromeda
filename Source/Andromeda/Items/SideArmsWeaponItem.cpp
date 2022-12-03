// Fill out your copyright notice in the Description page of Project Settings.


#include "SideArmsWeaponItem.h"


void USideArmsWeaponItem::LeftMousePressed_Implementation(USkeletalMeshComponent* MeshComponent)
{
	AttackWithCombo(MeshComponent);
}

void USideArmsWeaponItem::AttackWithCombo(USkeletalMeshComponent* MeshComponent)
{
	FName SectionName = AttackMontage->GetSectionName(ComboCounter);
	//PrintInfo(SectionName.ToString());

	UAnimInstance * AnimInstance = (MeshComponent)? MeshComponent->GetAnimInstance() : nullptr; //copied & modified from ACharacter::PlayAnimMontage -> we want to change sections in current montage, not to play another
	if( AttackMontage && AnimInstance )
	{
		if( SectionName == FName("Default"))
		{
			AnimInstance->Montage_Play(AttackMontage, 1);
		}
		else
		{
			AnimInstance->Montage_JumpToSection(SectionName, AttackMontage); 
		}
		
		ComboCounter++;
	}
}