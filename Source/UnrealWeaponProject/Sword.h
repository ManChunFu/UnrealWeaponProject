// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Sword.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWEAPONPROJECT_API ASword : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ASword();
	
	virtual void Attack() override;
};
