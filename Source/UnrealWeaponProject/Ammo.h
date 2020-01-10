// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ammo.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class UNREALWEAPONPROJECT_API UAmmo : public UObject
{
	GENERATED_BODY()
private:

public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 MagazineSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 SpareAmmo = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 MagazineAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 MaxSpareAmmo = 200;


	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void OnAttack();
	//UFUNCTION()
	//	void Reload();
};
