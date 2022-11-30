// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotifyState.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Character/ModularCharacter.h"
#include "Andromeda/Items/WeaponItem.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#define PrintInfo(String) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, String)
#define PrintWarning(String) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Yellow, String)
#define PrintError(String) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, String)

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	IgnoreActors.Empty();
	PreviousLocations.Empty();
	TraceSockets.Empty();

	if(AModularCharacter* ModularCharacter = Cast<AModularCharacter>(MeshComp->GetOwner()))
	{
		Weapon = ModularCharacter->Weapon;
		TraceSockets = Weapon->SkeletalMesh->GetActiveSocketList();// collect all sockets
		
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


		PreviousLocations[i] = EndPoint;
		if(UKismetSystemLibrary::LineTraceSingle(Weapon, StartPoint, EndPoint, TraceTypeQuery3,
		                                         false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true))
		{
			IgnoreActors.AddUnique(HitResult.GetActor());

			if(AModularCharacter* ModularCharacter = Cast<AModularCharacter>(MeshComp->GetOwner()))
			{
				AController* Instigator = ModularCharacter->GetController();
			
				UGameplayStatics::ApplyDamage(HitResult.GetActor(), Weapon->WeaponItem->Damage, Instigator, Weapon->GetOwner(), UDamageType::StaticClass());

				FName WeaponName = Weapon->WeaponItem->WeaponStatisticName;

				ModularCharacter->SetWeaponStat(WeaponName, ModularCharacter->GetWeaponStat(WeaponName) + 20);

				//PrintInfo(HitResult.GetActor()->GetName());
				//PrintInfo(HitResult.BoneName.ToString());
			}
		}
	}
}