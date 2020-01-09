// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnrealWeaponProjectGameMode.h"
#include "UnrealWeaponProjectHUD.h"
#include "UnrealWeaponProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealWeaponProjectGameMode::AUnrealWeaponProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnrealWeaponProjectHUD::StaticClass();
}