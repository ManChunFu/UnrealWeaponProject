// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Enemy.h"
#include "UnrealWeaponProject/GameLevelManager.h"


void ASpawnPoint::SpawnEnemy()
{
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation().Add(0.f, 180.f, 0.f);

	UWorld* World = GetWorld();

	if (World)
	{
		for (int32 Cout = 0; Cout < ActorSpawnAmout; Cout++)
		{
			try
			{
				GetWorld()->SpawnActor<AEnemy>(ActorToSpawn, Location, Rotation);
			}
			catch (const std::exception&)
			{	
				UE_LOG(LogTemp, Warning, TEXT("Failed in SpawnEnemy"));
			}			
		}
	}
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy();

	//GameLevelManager->RegisterSpawnEnemy(ActorSpawnAmout));
}





