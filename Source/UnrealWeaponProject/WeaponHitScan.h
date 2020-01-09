// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponRangedBase.h"
#include "WeaponHitScan.generated.h"


/**
 * 
 */
UCLASS()
class UNREALWEAPONPROJECT_API AWeaponHitScan : public AWeaponRangedBase
{
	GENERATED_BODY()
protected:


    virtual void Attack() override;
};
