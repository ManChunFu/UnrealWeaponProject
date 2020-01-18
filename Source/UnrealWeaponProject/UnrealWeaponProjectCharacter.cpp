// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnrealWeaponProjectCharacter.h"
#include "Engine/World.h"
#include "UnrealWeaponProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AUnrealWeaponProjectCharacter



void AUnrealWeaponProjectCharacter::RotateCamera(float test)
{
	AddControllerYawInput(test);
	
}

void AUnrealWeaponProjectCharacter::PitchCamera(float test)
{
	AddControllerPitchInput(test);
}

AUnrealWeaponProjectCharacter::AUnrealWeaponProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}

void AUnrealWeaponProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUnrealWeaponProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event

	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUnrealWeaponProjectCharacter::StartAttack);
	//PlayerInputComponent->BindAction("Fire", IE_Released, this, &AUnrealWeaponProjectCharacter::StopAttack);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AUnrealWeaponProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnrealWeaponProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUnrealWeaponProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUnrealWeaponProjectCharacter::LookUpAtRate);
}


void AUnrealWeaponProjectCharacter::EquipWeapon(AWeapon* Weapon)
{
	if (Weapon)
	{
		GetCapsuleComponent()->IgnoreActorWhenMoving(Weapon, true);
		Weapon->Equip(this, Mesh1P, "GripPoint");
		EquippedWeapon = Weapon;
	}
}

void AUnrealWeaponProjectCharacter::DropWeapon()
{
	if (EquippedWeapon)
	{
		GetCapsuleComponent()->IgnoreActorWhenMoving(EquippedWeapon, false);
		EquippedWeapon->Drop();
		EquippedWeapon = nullptr;
	}
}

void AUnrealWeaponProjectCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUnrealWeaponProjectCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AUnrealWeaponProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealWeaponProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

