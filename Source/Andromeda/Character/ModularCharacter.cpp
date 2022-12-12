// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularCharacter.h"
#include "Andromeda/Combat/WeaponComponent.h"
#include "Andromeda/Equipment/WeaponItem.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "../Equipment/Item.h"
#include "../Equipment/InventoryComponent.h"
#include "Andromeda/Interfaces/Interactable.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AModularCharacter::AModularCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	Weapon->SetupAttachment(GetMesh(), "LeftHipSocket");

	
	//// CAMERA
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetMesh(), "head");
	Camera->bUsePawnControlRotation = true;
	Camera->SetFieldOfView(110.f);

	
	//// CHARACTER BODY
	GetCapsuleComponent()->SetCapsuleRadius(25.f);
	GetMesh()->SetRelativeLocation(FVector(-20.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	//// INITIALIZE INVENTORY
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;
	
	for(FName WeaponStatName : UWeaponItem::GetWeapons())
		WeaponsStats.FindOrAdd(WeaponStatName, 0);

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
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AModularCharacter::Interact);

	PlayerInputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AModularCharacter::LeftMouseClick);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AModularCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AModularCharacter::StopSprinting);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AModularCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AModularCharacter::EndCrouch);
	
}

// Called when the game starts or when spawned
void AModularCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AModularCharacter::Tick(float DeltaSeconds)
{
	AActor* CurrentlyViewedObject = CastLineTrace();

	if( CurrentlyViewedObject != LastSeenInteractableObject)
	{
		if(LastSeenInteractableObject != nullptr)
		{
			IInteractable::Execute_IsNoLongerLookedAt(LastSeenInteractableObject, this);
		}
		LastSeenInteractableObject = CurrentlyViewedObject;
	}
	Super::Tick(DeltaSeconds);
}

void AModularCharacter::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); // Blueprint event.
	}
}

void AModularCharacter::ApplyRagdoll()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.f);
}

void AModularCharacter::InteractWithActor(AActor* InteractableActor)
{
	if(InteractableActor != nullptr)
	{
		IInteractable::Execute_Interact(InteractableActor,this);
	}
}

AActor* AModularCharacter::CastLineTrace()
{
	FHitResult HitResult;
	FVector Start = Camera->GetComponentLocation();
	FVector End = Camera->GetForwardVector() * 200 + Start;
	if(UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery2, false, {}, EDrawDebugTrace::None, HitResult, true ))
	{
		if( HitResult.GetActor()->Implements<UInteractable>() )
		{
			if(IInteractable::Execute_CanBeInteractedWith(HitResult.GetActor(), this))
			{
				return HitResult.GetActor();
			}
		}
	}
	return nullptr;
}

void AModularCharacter::LeftMouseClick()
{
	if(Weapon->IsWeaponEquipped() && CharacterState !=  ECharacterState::ATTACK)
	{
		Weapon->WeaponItem->LeftMousePressed(GetMesh());
	}

	if(Weapon->IsWeaponAtRest()  && CharacterState !=  ECharacterState::EQUIP)
	{
		Weapon->PlayEquipAnimation(this);
	}
}

void AModularCharacter::LeftMouseRelease()
{
	Weapon->WeaponItem->LeftMouseReleased(GetMesh());
}

void AModularCharacter::OnActorLoaded()
{
	
}

void AModularCharacter::SetCurrentStat(float FCharacterStats::* StatsField, float Value)
{
	CurrentsStats.*StatsField = Value;
}
void AModularCharacter::SetMaxStat(float FCharacterStats::* StatsField, float Value)
{
	MaxStats.*StatsField = Value;
}
void AModularCharacter::SetStatExp(float FCharacterStats::* StatsField, float Value)
{
	StatsEXP.*StatsField = Value;
}

void AModularCharacter::SetWeaponStat(FName StatName, float Value)
{
	if(!WeaponsStats.Contains(StatName))
		return;
	
	WeaponsStats[StatName] = Value;
}

float AModularCharacter::GetWeaponStat(FName StatName)
{
	if(!WeaponsStats.Contains(StatName))
		return 0;
	
	return WeaponsStats[StatName];
}

bool AModularCharacter::UseStamina(float StaminaToUse)
{
	CurrentsStats.Stamina = FMath::Clamp(CurrentsStats.Stamina - StaminaToUse, 0.f, 100.f);

	return (CurrentsStats.Stamina > 0);
}
