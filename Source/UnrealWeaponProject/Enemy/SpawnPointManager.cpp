// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPointManager.h"
#include "SpawnPoint.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ASpawnPointManager::ASpawnPointManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnPointManager::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	
	if (World)
	{
		World->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnPointManager::Spawn, SpawnRate, true);
	}
}

// Called every frame
void ASpawnPointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPointManager::Spawn()
{
	for (auto point : SpawnPoint)
	{
		if (point->ActiveEnemy() == 0)
		{
			point->SpawnEnemy();
		}
	}
}




