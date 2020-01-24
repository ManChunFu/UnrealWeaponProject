// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "../UnrealWeaponProjectCharacter.h"
#include "WeaponComponentInterface.h"
#include "FireModeComponent.h"
#include "Camera/CameraComponent.h"
#include "UnrealWeaponProject/UnrealWeaponProjectHUD.h"
#include "HitscanComponent.h"
#include "ProjectileComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	FireModeComponent = CreateDefaultSubobject<UFireModeComponent>(TEXT("FireMode"));
	AmmoComponent = CreateDefaultSubobject<UAmmoComponent>(TEXT("Ammo"));
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
		if (AmmoComponent->Reload())
		{
			for (auto Component : CachedComponents)
			{
				IWeaponComponentInterface::Execute_OnWeaponReload(Component);
			}
		}
	}
}

void AWeapon::Attack_Implementation()
{
	for (auto Component : CachedComponents)
	{
		IWeaponComponentInterface::Execute_OnWeaponAttack(Component);
	}
}

bool AWeapon::TryAttack()
{
	if (CanAttack())
	{
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

	// Get access to hitscancomponent class in order to get Damage value later
	HitscanComponent = FindComponentByClass<UHitscanComponent>();
	ProjectileComponent = FindComponentByClass<UProjectileComponent>();

}

void AWeapon::StartAttack_Implementation()
{
	if (FireModeComponent)
	{
		FireModeComponent->Start();
	}
	if (HitscanComponent != nullptr)
	{
		float Damage = HitscanComponent->Damage;
		PrintDamagePerShotOnHUD(Damage, "");
	}

}

void AWeapon::StopAttack_Implementation()
{
	if (FireModeComponent)
	{
		FireModeComponent->Stop();
	}
}

void AWeapon::PrintDamagePerShotOnHUD(float Value, FString Multiplier)
{
	AUnrealWeaponProjectHUD* UnrealWeaponProjectHUD = Cast<AUnrealWeaponProjectHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (FireModeComponent)
	{
		if (FireModeComponent->CurrentFireMode == EFireMode::BurstFire)
		{
			Multiplier = "x 3";
		}
		else if ((AmmoComponent->MagazineAmmo - AmmoComponent->CurrentAmmoCount) > 1)
		{
		}
		else 
		{
			Multiplier = "";
		}
	}

	if (UnrealWeaponProjectHUD)
	{
		UnrealWeaponProjectHUD->PrintDamagePerShot(Value, Multiplier);
	}
}


