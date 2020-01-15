// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevelManager.generated.h"

class ASpawnPoint;
class AEnemy;

/**
 * 
 */
UCLASS()
class UNREALWEAPONPROJECT_API AGameLevelManager : public ALevelScriptActor
{
	GENERATED_BODY()

		AGameLevelManager();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	ASpawnPoint* SpawnPoint = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	AEnemy* Enemy = nullptr;

	void RegisterEnemyDeath();
	void RegisterSpawnEnemy(int32 ActorSpawnAmout);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	int32 TotalSpawnedEnemy = 0;
private:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
