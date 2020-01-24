// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "WeaponComponentInterface.h"
#include "ProjectileComponent.generated.h"


UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class UNREALWEAPONPROJECT_API UProjectileComponent : public UActorComponent, public IWeaponComponentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Weapon")
		int32 BulletsPerShot = 1;
	UPROPERTY(VisibleInstanceOnly, Category = "Weapon")
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

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float Damage = 10.f;

	UFUNCTION(BlueprintCallable)
		TArray<AProjectile*> FireProjectile(float InaccuracyZ, float InaccuracyY, FTransform OverrideSpawn);


	

};
