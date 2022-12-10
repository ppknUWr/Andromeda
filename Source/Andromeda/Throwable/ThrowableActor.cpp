// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Andromeda/Items/WeaponItem.h"

// Sets default values
AThrowableActor::AThrowableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	SetRootComponent(Capsule);
	StaticMesh->SetupAttachment(Capsule);
	ProjectileMovement->Deactivate();
	ProjectileMovement->InitialSpeed = 300;
}

// Called when the game starts or when spawned
void AThrowableActor::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponItem)
	{
		StaticMesh->SetStaticMesh(WeaponItem->PickupMesh);
	}
	
}

// Called every frame
void AThrowableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrowableActor::ActivateProjectile()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	ProjectileMovement->Activate();
	ProjectileMovement->SetUpdatedComponent(Capsule);
}

