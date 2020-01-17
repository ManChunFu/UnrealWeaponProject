// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "MeleeSpear.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWEAPONPROJECT_API AMeleeSpear : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<UDamageType> DamageClass;

	UFUNCTION()
	void OnHit(AActor* ThisActor, AActor* OtherActor);


	
	
};
