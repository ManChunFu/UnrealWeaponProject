// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "TimerManager.h"
#include "Engine/World.h" 

// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	BarrelEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Barrel End"));
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->AttachToComponent(ArmsMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GripPoint");
	WeaponMesh->Transform
	RootComponent = ArmsMesh;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

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


