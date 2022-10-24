// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "../Combat/WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AModularCharacter::AModularCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

	Weapon = CreateDefaultSubobject<UWeaponComponent>("Weapon");
	Weapon->SetupAttachment(BodyParts[GetBodyPartIndex(EBodyPart::ARMS)], "RightHandSocket");

	
	//// CAMERA
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetMesh(), "head");
	Camera->bUsePawnControlRotation = true;
	Camera->SetFieldOfView(110.f);

	//// CHARACTER BODY
	GetCapsuleComponent()->SetCapsuleRadius(25.f);
	GetMesh()->SetRelativeLocation(FVector(-20.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	
}

float AModularCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentsStats.Health = FMath::Clamp(CurrentsStats.Health - DamageAmount, 0.f, MaxStats.Health);

	if (CurrentsStats.Health == 0)
	{
		ApplyRagdoll();
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AModularCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AModularCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AModularCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AModularCharacter::LeftMouseClick);
}

// Called when the game starts or when spawned
void AModularCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AModularCharacter::ApplyRagdoll()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.f);
}

void AModularCharacter::SetStat(float FCharacterStats::* StatsField, float Value)
{
	CurrentsStats.*StatsField = Value;
}

bool AModularCharacter::UseStamina(float StaminaToUse)
{
	CurrentsStats.Stamina = FMath::Clamp(CurrentsStats.Stamina - StaminaToUse, 0.f, 100.f);

	return (CurrentsStats.Stamina > 0);
}
