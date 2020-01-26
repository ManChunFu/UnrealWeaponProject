// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "Weapon.h"
#include "WeaponComponentInterface.h"
#include "FireModeComponent.generated.h"

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	SemiAuto	UMETA(DisplayName = "Semi Auto"),
	FullAuto	UMETA(DisplayName = "Full Auto"),
	BurstFire	UMETA(DisplayName = "Burst Fire"),
};

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class UNREALWEAPONPROJECT_API UFireModeComponent : public UActorComponent, public IWeaponComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFireModeComponent();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		TArray<EFireMode> AllowedFireModes;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Weapon")
		EFireMode CurrentFireMode;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Weapon")
		AWeapon* Weapon = nullptr;



	// Semi Auto Settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|SemiAuto")
		float SemiAutoAttackPerSecond = 5.f;

	// Burst Settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Burstfire")
		int32 AttacksPerBurst = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Burstfire")
		float BurstDelay = 0.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Burstfire")
		float BurstsPerSecond = 3.f;

	// AutoAttack Settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|FullAuto")
		float AutoAttacksPerSecond = 5.f;

	// Next attack times multiplied by this to prevent timers desyncing with attack times
	float NextAttackMargin = 0.90f;

private:
	

public:

	void BeginPlay();

	/** Toggles between allowed fire modes */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void ChangeFireMode();

	/** Outer Burst Function that loops the burst lambda */
	UFUNCTION()
		void Burst();


	UFUNCTION()
		void Attack();
	
	/** Start this fire mode component */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Start();
	/** Stop this fire mode component */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Stop();
private:

	virtual bool CanAttack_Implementation();

	float NextAttackTime = -1.f;
	bool bBursting = false;
	FTimerHandle FireHandle;
	FTimerHandle BurstHandle;
	FTimerDelegate BurstDelegate;
	int32 BurstCounter = 0;

	/**
	*Print the shot rate on UI when fire the weapon
	*/
	void PrintShotRateOnHUD(float Value);
};
