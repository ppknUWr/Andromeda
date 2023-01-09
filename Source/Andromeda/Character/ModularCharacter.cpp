// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularCharacter.h"
#include "NiagaraComponent.h"
#include "SkeletalMeshMerge.h"
#include "Andromeda/Components/ActionComponent.h"
#include "Andromeda/Components/InventoryComponent.h"
#include "Andromeda/Components/WeaponComponent.h"
#include "Andromeda/Items/WeaponItem.h"
#include "Andromeda/Items/Coins.h"
#include "Andromeda/Interfaces/Interactable.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Andromeda/Items/Item.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SkeletalMergingLibrary.h"
#include "Andromeda/Actions/WeaponEquipAction.h"

// Sets default values
AModularCharacter::AModularCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//// BODY PARTS AND ARMOUR
	CharacterMeshes.FindOrAdd(EBodyPart::HEAD, nullptr);
	CharacterMeshes.FindOrAdd(EBodyPart::TORSO, nullptr);
	CharacterMeshes.FindOrAdd(EBodyPart::ARMS, nullptr);
	CharacterMeshes.FindOrAdd(EBodyPart::LEGS, nullptr);
	CharacterMeshes.FindOrAdd(EBodyPart::FEET, nullptr);
	
	//// WEAPONS
	LeftHandWeapon = CreateDefaultSubobject<UWeaponComponent>("LeftHandWeapon");
	RightHandWeapon = CreateDefaultSubobject<UWeaponComponent>("RightHandWeapon");
	LeftHandWeapon->SetupAttachment(GetMesh(), "RightHipSocket");
	RightHandWeapon->SetupAttachment(GetMesh(), "LeftHipSocket");

	//// SPRING ARM
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 150.f;
	SpringArm->TargetOffset = FVector(0.f, 45.f, 30.f);
	
	
	//// CAMERA
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetMesh(), "head");
	Camera->bUsePawnControlRotation = true;
	Camera->SetFieldOfView(110.f);

	//// ACTION COMPONENT
	ActionComponent = CreateDefaultSubobject<UActionComponent>("ActionComponent");
	
	//// CHARACTER BODY
	GetCapsuleComponent()->SetCapsuleRadius(25.f);
	GetMesh()->SetRelativeLocation(FVector(-20.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	//// INITIALIZE INVENTORY
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	//// INITIALIZE COINS
	Coins = CreateDefaultSubobject<UCoins>("Coins");

	PlayerTrading = false;
	
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
	
	PlayerInputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AModularCharacter::MouseButtonPressed);
	PlayerInputComponent->BindAction("LeftMouseClick", IE_Released, this, &AModularCharacter::MouseButtonReleased);

	PlayerInputComponent->BindAction("RightMouseClick", IE_Pressed, this, &AModularCharacter::MouseButtonPressed);
	PlayerInputComponent->BindAction("RightMouseClick", IE_Released, this, &AModularCharacter::MouseButtonReleased);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AModularCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AModularCharacter::StopSprinting);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AModularCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AModularCharacter::EndCrouch);
	
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &AModularCharacter::ZoomIn);
	PlayerInputComponent->BindAction("ZoomIn", IE_Repeat, this, &AModularCharacter::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &AModularCharacter::ZoomOut);
	PlayerInputComponent->BindAction("ZoomOut", IE_Repeat, this, &AModularCharacter::ZoomOut);
}

// Called when the game starts or when spawned
void AModularCharacter::BeginPlay()
{
	Super::BeginPlay();

	MergeMeshes();
}

void AModularCharacter::Tick(float DeltaSeconds)
{
	AActor* CurrentlyViewedObject = CastLineTrace();
	if(InteractionWidgetRef)
	{
		if(CurrentlyViewedObject)
		{
			InteractionWidgetRef->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			InteractionWidgetRef->SetVisibility(ESlateVisibility::Hidden);
		}
		
	}

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

void AModularCharacter::BuyItem(UItem* Item)
{
	if (!Item)
	{
		return;
	}

	if (Coins->Coins > Item->BuyPrice)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, "Buy item");
		Coins->Coins -= Item->BuyPrice;
		TraderCoins->Coins += Item->BuyPrice;

		TraderInventory->ExchangeItem(Item, Inventory);
	}
	else
	{
		// Show some UI message that user doesn't have enough coins.
	}
}

void AModularCharacter::SellItem(UItem* Item)
{
	if (!Item)
	{
		return;
	}

	if (!TraderInventory)
	{
		return;
	}

	if (TraderCoins->Coins > Item->SellPrice)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, "Sell item");
		TraderCoins->Coins -= Item->SellPrice;
		Coins->Coins += Item->SellPrice;
		Inventory->ExchangeItem(Item, TraderInventory);
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
	if( InteractableActor != nullptr )
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
	if(UKismetSystemLibrary::LineTraceSingle(this, Start, Camera->GetForwardVector() * 20000 + Start, TraceTypeQuery2, false, {}, EDrawDebugTrace::None, HitResult, true ))
	{
		if (spellNumber == 2  && RightHandWeapon->WeaponItem != nullptr && Spell != nullptr && RightHandWeapon->WeaponItem->GetName().Contains("magic"))
		{
			lookAtPosition = HitResult.Location;
			lookAtPosition.Z = GetActorLocation().Z+50;
			Spell->SetActorLocation(lookAtPosition);
			Spell->SpellComponent->SetWorldLocation(lookAtPosition);

		}
	}
	return nullptr;
}

void AModularCharacter::MouseButtonPressed(FKey Key)
{
	UWeaponComponent* WeaponComponent = (Key == EKeys::LeftMouseButton) ? RightHandWeapon : LeftHandWeapon;
	
	if(Key == EKeys::LeftMouseButton)
	{
		OnLeftMouseButtonClicked.Broadcast(IE_Pressed);
	}
	else
	{
		OnRightMouseButtonClicked.Broadcast(IE_Pressed);
	}

	if(!WeaponComponent->IsWeaponEquipped())
	{
		ActionComponent->AddAction(UWeaponEquipAction::StaticClass(), {{"WeaponComponent", WeaponComponent}});
	}
	
	if(WeaponComponent->WeaponItem)
	{
		WeaponComponent->WeaponItem->ButtonPressed(this, Key);
	}
}

void AModularCharacter::MouseButtonReleased(FKey Key)
{
	UWeaponComponent* WeaponComponent = (Key == EKeys::LeftMouseButton) ? RightHandWeapon : LeftHandWeapon;

	if(Key == EKeys::LeftMouseButton)
	{
		OnLeftMouseButtonClicked.Broadcast(IE_Released);
	}
	else
	{
		OnRightMouseButtonClicked.Broadcast(IE_Released);
	}
	
	if (WeaponComponent->WeaponItem)
	{
		WeaponComponent->WeaponItem->ButtonReleased(this, Key);
	}
}

void AModularCharacter::OnActorLoaded()
{
	
}

void AModularCharacter::MergeMeshes()
{
	FSkeletalMeshMergeParams SkeletalMeshMergeParams;
	
	TArray<TObjectPtr<USkeletalMesh>> MeshesToMerge;
	CharacterMeshes.GenerateValueArray(MeshesToMerge);
	
	SkeletalMeshMergeParams.MeshesToMerge = MeshesToMerge;
	SkeletalMeshMergeParams.Skeleton = CharacterSkeleton;
	
	GetMesh()->SetSkeletalMesh(USkeletalMergingLibrary::MergeMeshes(SkeletalMeshMergeParams));
}

void AModularCharacter::ZoomIn()
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength - 10.f, 150.f, 450.f);
	if (SpringArm->TargetArmLength == 150.f)
	{
		Camera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "head");
		Camera->SetRelativeLocation(FVector(5.f, 15.f, 0.f));
		Camera->bUsePawnControlRotation = true;
		SpringArm->bUsePawnControlRotation = false;
	}
}

void AModularCharacter::ZoomOut()
{
	if (SpringArm->TargetArmLength == 150.f)
	{
		Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Camera->bUsePawnControlRotation = false;
		SpringArm->bUsePawnControlRotation = true;
	}
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + 10.f, 150.f, 450.f);
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
