// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPointManager.generated.h"

class ASpawnPoint;

UCLASS()
class UNREALWEAPONPROJECT_API ASpawnPointManager : public AActor
{
	GENERATED_BODY()
		

public:	
	// Sets default values for this actor's properties
	ASpawnPointManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TArray<ASpawnPoint*> SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SpawnRate = 5.f;


private:
	FTimerHandle TimerHandle;
	void Spawn();

};
