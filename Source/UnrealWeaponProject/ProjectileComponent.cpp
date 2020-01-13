// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UProjectileComponent::UProjectileComponent()
{
}


// Called when the game starts
void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

AProjectile* UProjectileComponent::FireProjectile(TSubclassOf<AProjectile> ProjectileClass,  AActor* Owner, FTransform CameraTransform, FTransform SpawnTransform, float SpeedMultiplier)
{
	//Will spawn two projectiles, One visible that does not have any collision.
	//One invisible with the correct spawn location (inside camera center) which is invisible but carries out the collision.
	// My reference is Blizzards Overwatch which from my testing uses a system like this to provide accurate shots while giving visual feedback that makes sense

	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		{
			FHitResult Hit;
			FCollisionQueryParams temp;
			temp.AddIgnoredActor(Owner);
			World->LineTraceSingleByChannel(Hit, CameraTransform.GetLocation(), 
				CameraTransform.GetLocation() + CameraTransform.GetRotation().GetForwardVector()*10000.f,
				ECollisionChannel::ECC_Camera, temp);
			DrawDebugLine(GetWorld(), CameraTransform.GetLocation(), CameraTransform.GetLocation() + CameraTransform.GetRotation().GetForwardVector() * 10000.f, FColor::Red, false, 1.f);
			
			if (Hit.bBlockingHit)
			{
				DrawDebugLine(GetWorld(), SpawnTransform.GetLocation(), Hit.Location, FColor::Green, false, 1.f);
				
			}
			else
			{
				DrawDebugLine(GetWorld(), SpawnTransform.GetLocation(), CameraTransform.GetLocation() + CameraTransform.GetRotation().GetForwardVector() * 10000.f, FColor::Red, false, 1.f);
			}

			AProjectile* VisibleProj = World->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform, Owner);
			VisibleProj->ProjectileSpeed *= SpeedMultiplier;
			VisibleProj->CollisionComp->SetCollisionProfileName("NoCollision");
			FRotator Rotation(((CameraTransform.GetLocation() + CameraTransform.GetRotation().GetForwardVector() * 10000.f)- SpawnTransform.GetLocation()).Rotation());
			SpawnTransform.SetRotation(Rotation.Quaternion());
			UGameplayStatics::FinishSpawningActor(VisibleProj, SpawnTransform);

			AProjectile* ProjectileInstance = World->SpawnActorDeferred<AProjectile>(ProjectileClass, CameraTransform, Owner);
			ProjectileInstance->ProjectileSpeed *= SpeedMultiplier;
			UGameplayStatics::FinishSpawningActor(ProjectileInstance, CameraTransform);


			return ProjectileInstance;
		}
	}
	return nullptr;
}
