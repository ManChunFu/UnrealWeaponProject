// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "../UnrealWeaponProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

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

// Called when the game starts
void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

TArray<AProjectile*> UProjectileComponent::FireProjectile(float InaccuracyZ, float InaccuracyY, FTransform OverrideSpawn, int AmountToSpawn, float SpeedMultiplier)
{
	TArray<AProjectile*> Projectiles;

	UWorld* const World = GetWorld();
	if (World != NULL && ProjectileClass->IsValidLowLevel())
	{
		for (int i = 0; i < AmountToSpawn; i++)
		{
			FTransform ProjSpawn;
			if (OverrideSpawn.Equals(FTransform()))
			{
				ProjSpawn = *Cast<AWeapon>(GetOwner())->SpawnPoint;
			}
			else
			{
				ProjSpawn = OverrideSpawn;
			}
			// Before spawning, rotate the spawn transform to account for inaccuracy
			FQuat ZRotation(FVector::UpVector, FMath::RandRange(-InaccuracyZ, InaccuracyZ) * PI / 180.f);
			FQuat YRotation(FVector::RightVector, FMath::RandRange(-InaccuracyY, InaccuracyY) * PI / -180.f);
			ProjSpawn.SetRotation(ProjSpawn.GetRotation() * ZRotation * YRotation);
			AProjectile* ProjectileInstance = World->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjSpawn, Holder);
			ProjectileInstance->ProjectileSpeed *= SpeedMultiplier;
			AUnrealWeaponProjectCharacter* Player = Cast<AUnrealWeaponProjectCharacter>(Holder);
			if (Player)
			{
				Player->GetCapsuleComponent()->IgnoreActorWhenMoving(ProjectileInstance, true);
			}
			UGameplayStatics::FinishSpawningActor(ProjectileInstance, ProjSpawn);
			Projectiles.Add(ProjectileInstance);
		}
	}
	return Projectiles;
}
// David är en bananrumpa






// Not used but if i have time i should fix this
			/*FHitResult Hit;
			FCollisionQueryParams temp;
			temp.AddIgnoredActor(Owner);
			World->LineTraceSingleByChannel(Hit, CameraTransform.GetLocation(),
				CameraTransform.GetLocation() + CameraTransform.GetRotation().GetForwardVector() * 100000.f,
				ECollisionChannel::ECC_Camera, temp);



			if (bDebugLine)
			{
				DrawDebugLine(GetWorld(), CameraTransform.GetLocation(), CameraTransform.GetLocation() + CameraTransform.GetRotation().GetForwardVector() * 10000.f, FColor::Red, false, 1.f);

				if (Hit.bBlockingHit)
				{
					DrawDebugLine(GetWorld(), SpawnTransform.GetLocation(), Hit.Location, FColor::Green, false, 1.f);

				}
				else
				{
					DrawDebugLine(GetWorld(), SpawnTransform.GetLocation(), CameraTransform.GetLocation() + CameraTransform.GetRotation().GetForwardVector() * 10000.f, FColor::Red, false, 1.f);
				}
			}
			if (Hit.bBlockingHit)
			{
				FRotator Rotation((Hit.Location - SpawnTransform.GetLocation()).Rotation());
				SpawnTransform.SetRotation(Rotation.Quaternion());
			}*/


			// not using at the moment
			//// Make visible, fake bullet
			//AProjectile* VisibleProj = World->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform, Owner);
			//VisibleProj->ProjectileSpeed *= SpeedMultiplier;
			//VisibleProj->CollisionComp->SetCollisionProfileName("PhantomProjectile");
			//UGameplayStatics::FinishSpawningActor(VisibleProj, SpawnTransform);