// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealWeaponProjectGameMode.generated.h"

UCLASS(minimalapi)
class AUnrealWeaponProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AUnrealWeaponProjectGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> WeaponHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	
};



