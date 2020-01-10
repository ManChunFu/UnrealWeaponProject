// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "TimerManager.h"
#include "Engine/World.h" 



// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Root"));
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	BarrelEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Barrel End"));
	
	BarrelEnd->SetupAttachment(WeaponMesh);

	

	RootComponent = WeaponRoot;
	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	
	Super::BeginPlay();

}

void AWeaponBase::OnConstruction(const FTransform& Transform)
{
	ArmsMesh->AttachToComponent(WeaponRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ArmsMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	ArmsMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	WeaponMesh->AttachToComponent(ArmsMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GripPoint");
}

void AWeaponBase::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon Start Attack"));
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AWeaponBase::Attack, AttackRate, bAutoAttack);
	Attack();
}


void AWeaponBase::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}

void AWeaponBase::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon attack"));
}


