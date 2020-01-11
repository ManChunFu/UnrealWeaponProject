// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "AmmoComponent.h"
#include "Components/ArrowComponent.h"
#include "Weapon.generated.h"

UCLASS()
class UNREALWEAPONPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()


		UPROPERTY(VisibleAnywhere, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		USkeletalMeshComponent* ArmsMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		USceneComponent* WeaponRoot = nullptr;

	


public:
	AWeapon();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
		UArrowComponent* BarrelEnd = nullptr;
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
		void StartAttacking();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
		void Reload();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
		void StopAttacking();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
		void Attack();

};
