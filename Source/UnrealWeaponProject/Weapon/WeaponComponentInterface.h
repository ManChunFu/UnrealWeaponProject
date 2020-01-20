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
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void OnWeaponDropped();
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void OnWeaponEquipped();

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};