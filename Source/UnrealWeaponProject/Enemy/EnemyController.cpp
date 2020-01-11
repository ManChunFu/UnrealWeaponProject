// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"	



void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	AEnemy* ControlledEnemy = GetControlledEnemy();
	ACharacter* PlayerCharacter = GetPlayer();

	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyController can't find player."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemeyController: %s found player: %s"), *(ControlledEnemy->GetName()), *(PlayerCharacter->GetName()));
	}
}

AEnemy* AEnemyController::GetControlledEnemy() const
{
	return Cast<AEnemy>(GetCharacter());
}

ACharacter* AEnemyController::GetPlayer() const
{
	ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	if (!PlayerCharacter)
	{
		return nullptr;
	}
	else
	{
		return Cast<ACharacter>(PlayerCharacter);
	}

}
