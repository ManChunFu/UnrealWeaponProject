// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "MeleeSpear.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWEAPONPROJECT_API AMeleeSpear : public AWeaponBase
{
	GENERATED_BODY()
	
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString Name = "Spear";
	virtual void Attack() override;
};
