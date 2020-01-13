// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Engine/Engine.h>

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float AEnemy::TakeDamage(float DamageAmout, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(DamageAmout, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		CurrentHealth -= ActualDamage;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Currernt Healt: "));
			
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::SanitizeFloat(CurrentHealth));

		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (CurrentHealth <= 0.f)
		{
			SetLifeSpan(0.001f);
		}
	}

	return ActualDamage;
}



