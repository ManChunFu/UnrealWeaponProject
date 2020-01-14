// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevelManager.h"
#include "Enemy/SpawnPoint.h"
#include "Enemy/Enemy.h"

AGameLevelManager::AGameLevelManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameLevelManager::RegisterEnemyDeath()
{
	if (TotalSpawnedEnemy == 0)
		return;

	TotalSpawnedEnemy--;
}

void AGameLevelManager::RegisterSpawnEnemy(int32 ActorSpawnAmout)
{
	 TotalSpawnedEnemy += ActorSpawnAmout;
}

void AGameLevelManager::BeginPlay()
{
	Super::BeginPlay();

	/*if (SpawnPoint)
	{
		SpawnPoint->SpawnEnemy();
	}*/
}

void AGameLevelManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*if (TotalSpawnedEnemy == 0)
	{
		SpawnPoint->SpawnEnemy();
	}*/
}
