// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Enemy.h"
#include "SpawnPointManager.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"


void ASpawnPoint::SpawnEnemy()
{
	FActorSpawnParameters SpawnParamters;
	SpawnParamters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation().Add(0.f, 180.f, 0.f);

	UWorld* World = GetWorld();
	

	if (World)
	{
		for (int32 Cout = 0; Cout < ActorSpawnAmout; Cout++)
		{
			try
			{
				Enemy.Add(GetWorld()->SpawnActor<AEnemy>(ActorToSpawn, Location, Rotation, SpawnParamters));
				Enemy.Last()->SpawnPoint = this;
			}
			catch (const std::exception&)
			{	
				UE_LOG(LogTemp, Warning, TEXT("Failed in SpawnEnemy"));
			}			
		}
	}
}

int ASpawnPoint::ActiveEnemy()
{
	return Enemy.Num();
}

void ASpawnPoint::RegisterEnemyDeath(AEnemy* DeadEnemy)
{
	if (Enemy.Num() > 0)
	{
		Enemy.RemoveAt(Enemy.Find(DeadEnemy));
	}
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy();
}







