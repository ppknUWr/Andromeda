// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AModularCharacter::AModularCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Health = MaxHealth;

	//// BODY PARTS
	BodyParts.Init(nullptr, GetBodyPartIndex(EBodyPart::COUNT));
	for (int i = 0; i < GetBodyPartIndex(EBodyPart::COUNT); i++)
	{
		UEnum* BodyPartNameEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EBodyPart"), true);
		FName ComponentName = FName(*BodyPartNameEnum->GetDisplayNameTextByIndex(i).ToString());

		BodyParts[i] = CreateDefaultSubobject<USkeletalMeshComponent>(ComponentName);
		BodyParts[i]->SetupAttachment(GetMesh());
		BodyParts[i]->SetMasterPoseComponent(GetMesh());
	}

	//// CAMERA
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(BodyParts[GetBodyPartIndex(EBodyPart::HEAD)], "head");
	Camera->bUsePawnControlRotation = true;
	Camera->SetFieldOfView(110.f);
	
	//// CHARACTER BODY
	GetCapsuleComponent()->SetCapsuleRadius(25.f);
	GetMesh()->SetRelativeLocation(FVector(-20.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
}

float AModularCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	SetHealth(Health - DamageAmount);

	if (Health == 0)
	{
		ApplyRagdoll();
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

// Called when the game starts or when spawned
void AModularCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AModularCharacter::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);
}

void AModularCharacter::ApplyRagdoll()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(3.f);
}


bool AModularCharacter::UseStamina(float StaminaToUse)
{
	Stamina = FMath::Clamp(Stamina - StaminaToUse, 0.f, 100.f);

	return (Stamina > 0);
}