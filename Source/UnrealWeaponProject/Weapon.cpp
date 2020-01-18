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
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetGenerateOverlapEvents(true);

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
	WeaponMesh->SetGenerateOverlapEvents(false);
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->AddImpulse(WeaponMesh->GetRightVector()*5000.f + Holder->GetRootComponent()->GetUpVector()*2000.f);
	StopAttacking();
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Holder = nullptr;

	// Wait two seconds before letting the weapon be overlappable again
	if (!DropDelegate.IsBound())
	{
		DropDelegate.BindLambda([=]
			{
				WeaponMesh->SetGenerateOverlapEvents(true);
			});
	}
	GetWorld()->GetTimerManager().SetTimer(DropHandle, DropDelegate, 2.f, false);
	
}

void AWeapon::Equip(USceneComponent* AttachTo, FName SocketName)
{
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->AttachToComponent(AttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

}


