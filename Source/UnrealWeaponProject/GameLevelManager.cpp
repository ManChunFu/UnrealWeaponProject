// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevelManager.h"
#include "Enemy/SpawnPoint.h"

void AGameLevelManager::RegisterSpawnedEnemy(int32 ActorSpawnAmout)
{
	TotalEnemy += ActorSpawnAmout;
}

void AGameLevelManager::RegisterEnemyDeath()
{
	TotalEnemy--;
	SpawnPoint->SpawnEnemy();
}

void AGameLevelManager::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnPoint)
	{
		SpawnPoint->SpawnEnemy();
	}
}
