// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPointManager.h"
#include "SpawnPoint.h"

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
	
}

// Called every frame
void ASpawnPointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto point : SpawnPoint)
	{
		if (point->ActiveEnemy() == 0)
		{
			point->SpawnEnemy();
		}
	}
}




