// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "SpawnPoint.generated.h"

class AEnemy;
class AGameLevelManager;

/**
 * 
 */
UCLASS()
class UNREALWEAPONPROJECT_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    TSubclassOf<AEnemy> ActorToSpawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
    int32 ActorSpawnAmout = 1;

    UFUNCTION(BlueprintCallable)
    void SpawnEnemy();

private:
    AGameLevelManager* GameLevelManager = nullptr;
    virtual void BeginPlay() override;
};
