// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponProjectile.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AWeaponProjectile::Attack()
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		{
			const FRotator SpawnRotation = GetActorRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			
			const FVector SpawnLocation = GetActorLocation();
			//const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// spawn the projectile at the muzzle
			FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, FVector::OneVector);
			AProjectile* ProjectileInstance = World->SpawnActorDeferred<AProjectile>(Projectile, SpawnTransform, this);


			UGameplayStatics::FinishSpawningActor(ProjectileInstance, SpawnTransform);
		}
	}
}
