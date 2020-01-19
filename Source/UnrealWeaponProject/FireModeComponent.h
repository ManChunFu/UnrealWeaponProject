// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "Weapon.h"
#include "FireModeComponent.generated.h"

class UAudioComponent;

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	SemiAuto	UMETA(DisplayName = "Semi Auto"),
	FullAuto	UMETA(DisplayName = "Full Auto"),
	BurstFire	UMETA(DisplayName = "Burst Fire")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALWEAPONPROJECT_API UFireModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFireModeComponent();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		TArray<EFireMode> AllowedFireModes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|AutoAttack")
		float AutoAttacksPerSecond = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Audio")
		class USoundBase* SoundCue;


private:
	int32 BurstCounter = 0;
	UFUNCTION()
		void Burst();

public:

	void BeginPlay();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void ChangeFireMode();

	UFUNCTION()
		void BurstFire();
	UFUNCTION()
		void Attack();


	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Start();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Stop();

private:

	bool CanAttack();

	float NextAttackTime = -1.f;
	bool bBursting = false;
	FTimerHandle FireHandle;
	FTimerHandle BurstHandle;
	FTimerDelegate BurstDelegate;

	UAudioComponent* SoundAudioComponent;
};
