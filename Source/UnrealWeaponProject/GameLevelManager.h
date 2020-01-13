// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevelManager.generated.h"

class ASpawnPoint;
/**
 * 
 */
UCLASS()
class UNREALWEAPONPROJECT_API AGameLevelManager : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	void RegisterSpawnedEnemy(int32 ActorSpawnAmout);
	void RegisterEnemyDeath();

private:
	int32 TotalEnemy = 0;
	ASpawnPoint* SpawnPoint;
};
