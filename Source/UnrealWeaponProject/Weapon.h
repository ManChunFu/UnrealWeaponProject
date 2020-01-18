// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "AmmoComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Weapon.generated.h"


UCLASS()
class UNREALWEAPONPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()
private:
	FTimerDelegate DropDelegate;
	FTimerHandle DropHandle;
public:
	AWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	//	USkeletalMeshComponent* ArmsMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UArrowComponent* BarrelEnd = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		AActor* Holder = nullptr;

	// If this is 0, the weapon can attack. Increment it if you want to suspend weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		int32 SuspendedFromAttack = 0;



protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Equip(USceneComponent* AttachTo, FName SocketName);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
		void StartAttacking();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
		void Reload();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
		void StopAttacking();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
		void Attack();
	UFUNCTION()
		void Drop();
private:
	

};
