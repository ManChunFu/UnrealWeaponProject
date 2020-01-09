// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "UnrealWeaponProjectProjectile.h"
#include "CoreMinimal.h"
#include "WeaponRangedBase.h"
#include "WeaponProjectile.generated.h"

/**
 *
 */
UCLASS()
class UNREALWEAPONPROJECT_API AWeaponProjectile : public AWeaponRangedBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float InitialForce = 2500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AProjectile> 
		Projectile = nullptr;

	virtual void Attack() override;
};
