// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Andromeda/Items/WeaponItem.h"

// Sets default values
AThrowableActor::AThrowableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	
	SetRootComponent(Sphere);
	StaticMesh->SetupAttachment(Sphere);

	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	ProjectileMovement->InitialSpeed = 1500;
	ProjectileMovement->MaxSpeed = 1500;
	ProjectileMovement->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovement->SetActive(false);
	
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
	ProjectileMovement->Activate();
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	
	
	GetWorldTimerManager().SetTimer(TimerHandle, [&]()
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetWorldTimerManager().ClearTimer(TimerHandle);
		
	}, 0.01f, false);
	
	
}

