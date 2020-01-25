// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "../UnrealWeaponProjectCharacter.h"
#include "RecoilComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../MathHelperFunctions.h"

// Sets default values for this component's properties
UProjectileComponent::UProjectileComponent()
{
}


void UProjectileComponent::OnWeaponDropped_Implementation()
{
	Holder = nullptr;
}

void UProjectileComponent::OnWeaponEquipped_Implementation(AActor* NewHolder)
{
	Holder = NewHolder;
}

void UProjectileComponent::OnWeaponAttack_Implementation()
{
	if (Recoil)
	{
		FireProjectile(Recoil->CurrentMaxRecoil, Recoil->CurrentMaxRecoil, Cast<AWeapon>(GetOwner())->GetSpawnPoint());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("No Recoil Component Found!"));
	FireProjectile(0.f, 0.f, Cast<AWeapon>(GetOwner())->GetSpawnPoint());	
}

// Called when the game starts
void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
	BulletsPerShot = Cast<AWeapon>(GetOwner())->BulletsPerShot;
	auto RecoilComp = GetOwner()->GetComponentByClass(URecoilComponent::StaticClass());
	if (RecoilComp)
	{
		Recoil = Cast<URecoilComponent>(RecoilComp);
	}
}

TArray<AProjectile*> UProjectileComponent::FireProjectile(float InaccuracyZ, float InaccuracyY, FTransform OverrideSpawn)
{
	TArray<AProjectile*> Projectiles;

	UWorld* const World = GetWorld();
	if (World != NULL && ProjectileClass->IsValidLowLevel())
	{
		for (int i = 0; i < BulletsPerShot; i++)
		{
			FTransform ProjSpawn;

			if (OverrideSpawn.Equals(FTransform()))
			{ ProjSpawn = Cast<AWeapon>(GetOwner())->GetSpawnPoint(); }
			else
			{ ProjSpawn = OverrideSpawn; }
			float ZOnCircle, YOnCircle;
			UMathHelperFunctions::GetRandomPointOnCircle(ZOnCircle, YOnCircle);
			// Before spawning, rotate the spawn transform to account for inaccuracy
			FQuat ZRotation(FVector::UpVector, ZOnCircle * InaccuracyZ * PI / 180.f);
			FQuat YRotation(FVector::RightVector, YOnCircle * InaccuracyY * PI / -180.f);
			ProjSpawn.SetRotation(ProjSpawn.GetRotation() * ZRotation * YRotation);


			AProjectile* ProjectileInstance = World->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjSpawn, Holder);
			ProjectileInstance->Damage = Damage;
			AUnrealWeaponProjectCharacter* Player = Cast<AUnrealWeaponProjectCharacter>(Holder);
			if (Player)
			{ Player->GetCapsuleComponent()->IgnoreActorWhenMoving(ProjectileInstance, true); }
			UGameplayStatics::FinishSpawningActor(ProjectileInstance, ProjSpawn);
			Projectiles.Add(ProjectileInstance);
		}
	}
	return Projectiles;
}
