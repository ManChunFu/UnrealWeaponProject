// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponentInterface.h"
#include "WeaponAnimationComponent.generated.h"

class AUnrealWeaponProjectCharacter;
class AWeapon;

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class UNREALWEAPONPROJECT_API UWeaponAnimationComponent : public UActorComponent, public IWeaponComponentInterface
{
	GENERATED_BODY()

public:
	/**
	* Sets default values for this component's properties
	*/
	UWeaponAnimationComponent();

protected:
	/**
	* Called when the game starts
	*/
	virtual void BeginPlay() override;

public:
	/**
	 * Called every frame
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	* This fire weapon animation plays when weapon fires
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* FireAnimationMontage;
	/**
	* This reload weapon animation plays when reloading magazine
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* ReloadAnimationMontage;
	/**
	* This particle system fires when weapon fires
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* MuzzleFlash;

	virtual void OnWeaponAttack_Implementation() override;
	virtual void OnWeaponReload_Implementation() override;

	AUnrealWeaponProjectCharacter* Player;
	AWeapon* Weapon;

};
