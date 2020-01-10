// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "ProjectileComponent.h"
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

void UProjectileComponent::FireProjectile(TSubclassOf<AActor> ProjectileClass, FTransform SpawnLocation)
{

	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		{
			//const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			AActor* ProjectileInstance = World->SpawnActorDeferred<AActor>(ProjectileClass, SpawnLocation, nullptr);

			UGameplayStatics::FinishSpawningActor(ProjectileInstance, SpawnLocation);
		}
	}

}
