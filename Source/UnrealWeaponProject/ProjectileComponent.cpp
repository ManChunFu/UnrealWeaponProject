// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileComponent.h"
#include "Engine/World.h"
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

void UProjectileComponent::FireProjectile(TSubclassOf<AProjectile> ProjectileClass,  AActor* Owner, FTransform SpawnLocation, float SpeedMultiplier)
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		{
			//const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
			AProjectile* ProjectileInstance = World->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnLocation, Owner);
			ProjectileInstance->ProjectileSpeed *= SpeedMultiplier;
			UGameplayStatics::FinishSpawningActor(ProjectileInstance, SpawnLocation);
		}
	}
}
