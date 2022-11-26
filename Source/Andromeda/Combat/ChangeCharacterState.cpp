// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeCharacterState.h"

#include "Andromeda/Character/ModularCharacter.h"

void UChangeCharacterState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(AModularCharacter* ModularCharacter = Cast<AModularCharacter>(MeshComp->GetOwner()))
	{
		ModularCharacter->CharacterState = DestinedCharacterState;
	}
}
