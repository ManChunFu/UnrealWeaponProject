// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "UnrealWeaponProjectCharacter.h"
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

AProjectile* UProjectileComponent::FireProjectile(TSubclassOf<AProjectile> ProjectileClass, AActor* Owner, FTransform CameraTransform, float SpeedMultiplier)
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		{
			// Spawn bullet from camera position

			FTransform CamSpawn = CameraTransform;
			//CamSpawn.SetLocation(CamSpawn.GetLocation() + CamSpawn.GetRotation().GetForwardVector() *50.f);
			AProjectile* ProjectileInstance = World->SpawnActorDeferred<AProjectile>(ProjectileClass, CamSpawn, Owner);
			ProjectileInstance->ProjectileSpeed *= SpeedMultiplier;
			AUnrealWeaponProjectCharacter* Player = Cast<AUnrealWeaponProjectCharacter>(Owner);
			if (Player)
			{
				Player->GetCapsuleComponent()->IgnoreActorWhenMoving(ProjectileInstance, true);
			}
			UGameplayStatics::FinishSpawningActor(ProjectileInstance, CamSpawn);


			return ProjectileInstance;
		}
	}
	return nullptr;
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