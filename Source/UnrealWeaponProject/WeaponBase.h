// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBase.generated.h"

UCLASS()
class UNREALWEAPONPROJECT_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

protected:

	// Timer to call next attack function
	FTimerHandle AttackTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		USkeletalMeshComponent* ArmsMesh = nullptr; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
		USceneComponent* BarrelEnd = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float AttackRate = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float Damage = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool bAutoAttack = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool bUseAmmo = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int32 CurrentAmmo = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int32 MaxAmmo = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		int32 ClipSize = 10;


	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;


	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void Attack();

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void StopFire();



};
