// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Root"));
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	BarrelEnd = CreateDefaultSubobject<UArrowComponent>(TEXT("Barrel End"));

	BarrelEnd->SetupAttachment(WeaponRoot);



	RootComponent = WeaponRoot;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	ArmsMesh->AttachToComponent(WeaponRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ArmsMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	ArmsMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	WeaponMesh->AttachToComponent(ArmsMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GripPoint");
	FAttachmentTransformRules BarrelAttachmentRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
}


