// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"	
#include "AIController.h"
#include "Enemy.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWEAPONPROJECT_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	AEnemy* GetControlledEnemy() const;
	ACharacter* GetPlayer() const;

	
};
