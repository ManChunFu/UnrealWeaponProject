// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnrealWeaponProjectGameMode.h"
#include "UnrealWeaponProjectHUD.h"
#include "UnrealWeaponProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void AUnrealWeaponProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	AUnrealWeaponProjectCharacter* MyCharacter = Cast<AUnrealWeaponProjectCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (WeaponHUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WeaponHUDClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

AUnrealWeaponProjectGameMode::AUnrealWeaponProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnrealWeaponProjectHUD::StaticClass();
}


