// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetCollisionProfileName("Weapon");
	BarrelEnd = CreateDefaultSubobject<UArrowComponent>(TEXT("Barrel End"));
	BarrelEnd->SetupAttachment(WeaponMesh);
	RootComponent = WeaponMesh;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	BarrelEnd->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

void AWeapon::Drop()
{
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->AddImpulse(WeaponMesh->GetRightVector()*5000.f);
	Holder = nullptr;
	DetachRootComponentFromParent();
}

void AWeapon::Equip(USceneComponent* AttachTo, FName SocketName)
{
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->AttachToComponent(AttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}


