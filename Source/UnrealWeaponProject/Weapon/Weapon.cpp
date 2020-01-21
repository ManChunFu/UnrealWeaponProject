// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "../UnrealWeaponProjectCharacter.h"
#include "WeaponComponentInterface.h"
#include "FireModeComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	FireModeComponent = CreateDefaultSubobject<UFireModeComponent>(TEXT("FireMode"));
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
	AmmoComponent = Cast<UAmmoComponent>(GetComponentByClass(UAmmoComponent::StaticClass()));


	CachedComponents = GetComponentsByInterface(UWeaponComponentInterface::StaticClass());
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	BarrelEnd->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

void AWeapon::Reload_Implementation()
{
	if (AmmoComponent)
	{
		AmmoComponent->Reload();
	}
}

bool AWeapon::TryAttack()
{
	if (CanAttack())
	{
		for (auto Component : CachedComponents)
		{
			IWeaponComponentInterface::Execute_OnWeaponAttack(Component);
		}
		Attack();
		return true;
	}
	return false;
}

void AWeapon::Drop()
{
	for (auto Component : CachedComponents)
	{
		IWeaponComponentInterface::Execute_OnWeaponDropped(Component);
	}

	WeaponMesh->SetGenerateOverlapEvents(false);
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->AddImpulse(WeaponMesh->GetRightVector() * 5000.f + Holder->GetRootComponent()->GetUpVector() * 2000.f);
	StopAttack();
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

bool AWeapon::CanAttack()
{
	for (auto Component : CachedComponents)
	{
		if (!IWeaponComponentInterface::Execute_CanAttack(Component))
		{
			return false;
		}
	}
	return true;
}

void AWeapon::Equip(AActor* NewHolder, USceneComponent* AttachTo, FName SocketName)
{
	Holder = NewHolder;
	if (Holder->IsA<AUnrealWeaponProjectCharacter>())
	{
		SpawnPoint = &Cast<AUnrealWeaponProjectCharacter>(Holder)->GetFirstPersonCameraComponent()->GetComponentTransform();

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Start Attack"));

		SpawnPoint = &BarrelEnd->GetComponentTransform();
	}
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->AttachToComponent(AttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);


	for (auto Component : CachedComponents)
	{
		IWeaponComponentInterface::Execute_OnWeaponEquipped(Component, Holder);
	}

}

void AWeapon::StartAttack_Implementation()
{
	FireModeComponent->Start();
}

void AWeapon::StopAttack_Implementation()
{
	FireModeComponent->Stop();
}


