// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/SpawnPoint.h"
#include "UnrealWeaponProjectGameState.h"

void AUnrealWeaponProjectGameState::RegisterSpawnedEnemy(int32 ActorSpawnAmout)
{
	TotalEnemy += ActorSpawnAmout;
}

void AUnrealWeaponProjectGameState::RegisterEnemyDeath()
{
	TotalEnemy--;


}
