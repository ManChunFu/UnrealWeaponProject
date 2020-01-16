// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "Weapon.h"
#include "FireModeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALWEAPONPROJECT_API UFireModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireModeComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Burstfire")
		int32 AttacksPerBurst = 3;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Burstfire")
		float BurstDelay = 0.05f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float AttacksPerSecond = 3.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Weapon")
		AWeapon* Weapon = nullptr;

private:
	int32 BurstCounter = 0;
	UFUNCTION()
		void Burst();

public:	

	void BeginPlay();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void AutoFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void BurstFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Attack();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Stop();

private:

	bool CanAttack();

	float LastAttackTime = -1.f;
	bool bBursting = false;
	FTimerHandle FireHandle;
	FTimerHandle BurstHandle;
	FTimerDelegate BurstDelegate;
};
