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

protected:

public:	

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void AutoFire(float RateOfFire, AWeapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")

		void BurstFire(float RateOfFire, int32 AttacksPerBurst);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Stop();

	FTimerHandle FireHandle;
};
