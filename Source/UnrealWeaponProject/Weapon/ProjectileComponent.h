// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "ProjectileComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALWEAPONPROJECT_API UProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProjectileComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable)
		AProjectile* FireProjectile(TSubclassOf<AProjectile> ProjectileClass, UPARAM(ref) AActor*& Owner, float InaccuracyZ, float InaccuracyY, FTransform OverrideSpawn, float SpeedMultiplier = 1.F);


};
