// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotifyState.h"

#include "WeaponComponent.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetSystemLibrary.h"

#define Print(String) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, String)

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	IgnoreActors.Empty();
	PreviousLocations.Empty();
	TraceSockets.Empty();

	if(AModularCharacter* ModularCharacter = Cast<AModularCharacter>(MeshComp->GetOwner()))
	{
		Weapon = ModularCharacter->Weapon;
		TraceSockets = Weapon->SkeletalMesh->GetActiveSocketList();
		
		for(int i = 0; i < TraceSockets.Num(); i++)
		{
			PreviousLocations.Add(TraceSockets[i]->GetSocketLocation(Weapon));
		}
	}

	
}

void UAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	FHitResult HitResult;

	for(int i = 0; i < TraceSockets.Num(); i++)
	{
		FVector StartPoint = PreviousLocations[i];
		FVector EndPoint = TraceSockets[i]->GetSocketLocation(Weapon);
		
		
		if(UKismetSystemLibrary::LineTraceSingle(Weapon, StartPoint, EndPoint, TraceTypeQuery3,
           			false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true))
		{
			IgnoreActors.AddUnique(HitResult.GetActor());
			Print(HitResult.GetActor()->GetHumanReadableName());
			Print(HitResult.BoneName.ToString());
		}

		PreviousLocations[i] = EndPoint;
	}
}
