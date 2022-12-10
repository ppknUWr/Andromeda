// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableActor.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class UProjectileMovementComponent;
class UWeaponItem;

UCLASS()
class ANDROMEDA_API AThrowableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Instanced)
		UWeaponItem* WeaponItem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void ActivateProjectile();

};
