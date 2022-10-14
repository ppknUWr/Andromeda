// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotifyState.h"

#include "Engine/SkeletalMeshSocket.h"

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	IgnoreActors.Empty();
}

void UAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	FHitResult HitResult;

	TArray<USkeletalMeshSocket*> TraceSockets = MeshComp->SkeletalMesh->GetActiveSocketList();

	for(int i = 0; i < TraceSockets.Num(); i++)
	{
		FVector EndPoint = TraceSockets[i]->GetSocketLocation(MeshComp);
		//todo: store previos frame socket locations, use them as StartPoint
		//GetWorld()->LineTraceSingleByObjectType()
	}
	
}
