// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponentInterface.h"
#include "HitscanComponent.generated.h"


UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class UNREALWEAPONPROJECT_API UHitscanComponent : public UActorComponent, public IWeaponComponentInterface
{
	GENERATED_BODY()
private:
	class URecoilComponent* Recoil = nullptr;
	class UCameraShakeComponent* Camshake = nullptr;
	UPROPERTY(VisibleInstanceOnly, Category = "Weapon")
	int32 BulletsPerShot = 1;
public:	
	// Sets default values for this component's properties
	UHitscanComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		bool bDrawDebugLine = false;

	/*
	* Damage apply per shot
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float Damage = 5.f;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		/**Fires a line trace. Inaccuracy determines how much the line should deviate from a straight line (works well with the recoil component)*/
		TArray<FHitResult> Fire(float InaccuracyZ, float InaccuracyY, bool bDebugLine);

	int ShotCount = 1;
	virtual void OnWeaponAttack_Implementation() override;
		
};
