// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALWEAPONPROJECT_API IWeaponComponentInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	void OnWeaponDropped();
	virtual void OnWeaponDropped_Implementation()
	{};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	bool CanAttack();
	virtual bool CanAttack_Implementation()
	{
		return true;
	};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	void OnWeaponAttack();
	virtual void OnWeaponAttack_Implementation()
	{};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	void OnWeaponEquipped(AActor* NewHolder);
	virtual void OnWeaponEquipped_Implementation(AActor* NewHolder)
	{};



	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
