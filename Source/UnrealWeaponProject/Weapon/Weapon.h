// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "AmmoComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Weapon.generated.h"

class UHitscanComponent;
class UProjectileComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponDropped);
UCLASS()
class UNREALWEAPONPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()
private:
	
	FTimerDelegate DropDelegate;
	FTimerHandle DropHandle;

	/** Pointer to the holders world location */
	const FTransform* SpawnPoint;
public:
	AWeapon();

	/** List of all the components attached to the weapon */
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TArray<UActorComponent*> CachedComponents;


	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnWeaponDropped WeaponDropped;

	/** Reference to the Weapon Mesh of the weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh = nullptr;

	/** Reference to the fire mode component of the weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	class UFireModeComponent* FireModeComponent = nullptr;

	/** Reference to the ammo component of the weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
		class UAmmoComponent* AmmoComponent = nullptr;


	/** Reference to the barrel endpoint of the weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UArrowComponent* BarrelEnd = nullptr;

	/** Reference to the holder of the weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
		AActor* Holder = nullptr;

	/** Amount of bullets per shot, like a shotgun */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		int32 BulletsPerShot = 1;
	
	/** @Return The Transform used by other components to spawn / start bullets */
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

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool CanAttack();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool TryAttack();

	UFUNCTION()
	void Drop();

	
private:
	UHitscanComponent* HitscanComponent;
	UProjectileComponent* ProjectileComponent;
	/*
	* Print damage value on UI each time weapon fires 
	*/
	void PrintDamagePerShotOnHUD(float Value, FString Multiplier);

};
