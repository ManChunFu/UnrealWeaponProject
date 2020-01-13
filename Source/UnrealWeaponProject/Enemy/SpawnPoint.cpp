// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Enemy.h"
#include "Engine/World.h"
#include "UnrealWeaponProject/GameLevelManager.h"

void ASpawnPoint::SpawnEnemy()
{
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation().Add(0.f, 180.f, 0.f);
	for (int32 Cout = 0; Cout < ActorSpawnAmout; Cout++)
	{
		GetWorld()->SpawnActor<AEnemy>(ActorToSpawn, Location, Rotation);
	}
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnEnemy();
	GameLevelManager->RegisterSpawnedEnemy(ActorSpawnAmout);
}

