// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "AmmoComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Weapon.generated.h"


class UProjectileComponent;
class AProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponDropped);
UCLASS()
class UNREALWEAPONPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()
private:
	
	FTimerDelegate DropDelegate;
	FTimerHandle DropHandle;

	// World location for any spawns caused by this weapon
	const FTransform* SpawnPoint;
public:
	AWeapon();

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TArray<UActorComponent*> CachedComponents;


	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnWeaponDropped WeaponDropped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	class UFireModeComponent* FireModeComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
		class UAmmoComponent* AmmoComponent = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	//	USkeletalMeshComponent* ArmsMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UArrowComponent* BarrelEnd = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
		AActor* Holder = nullptr;

	// If this is 0, the weapon can attack. Increment it if you want to suspend weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		int32 SuspendedFromAttack = 0;


	
	FORCEINLINE FTransform GetSpawnPoint()
	{
		FTransform Spawn;
		Spawn = *SpawnPoint;
		Spawn.SetLocation(Spawn.GetLocation() + SpawnPoint->GetRotation().GetForwardVector() * 50.f);
		return Spawn;
	}

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Equip(AActor* NewHolder, USceneComponent* AttachTo, FName SocketName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
		void StartAttack();
	virtual void StartAttack_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
		void StopAttack();
	virtual void StopAttack_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
		void Reload();
	virtual void Reload_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void Attack();
	virtual void Attack_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Weapon")
		void AltAttack();


	bool TryAttack();

	UFUNCTION()
		void Drop();

	bool CanAttack();
private:
	UProjectileComponent* ProjectileComponent;
	AProjectile* Projectile;

	void PrintDamagePerShotOnHUD(float Value, FString Multiplier);

};
