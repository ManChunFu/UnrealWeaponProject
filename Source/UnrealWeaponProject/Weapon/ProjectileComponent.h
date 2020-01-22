// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "WeaponComponentInterface.h"
#include "ProjectileComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALWEAPONPROJECT_API UProjectileComponent : public UActorComponent, public IWeaponComponentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		int32 ProjectilesToSpawn = 1;
	UPROPERTY(VisibleInstanceOnly, Category="Weapon")
		AActor* Holder = nullptr;

public:
	UProjectileComponent();

	virtual void OnWeaponDropped_Implementation() override;

	virtual void OnWeaponEquipped_Implementation(AActor* NewHolder) override;

protected:

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<AProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
		TArray<AProjectile*> FireProjectile(float InaccuracyZ, float InaccuracyY, FTransform OverrideSpawn, float SpeedMultiplier = 1.F);

	AProjectile* ProjectileInstance;


};
