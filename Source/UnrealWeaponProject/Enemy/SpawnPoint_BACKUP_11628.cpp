// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
<<<<<<< HEAD
#include "Enemy.h"
#include "Engine/World.h"
#include "UnrealWeaponProject/GameLevelManager.h"
=======
#include "Engine/World.h"
#include "Enemy.h"
>>>>>>> 61fe563a2f3cada65e781d5fc24a40a66bb0e78b

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

