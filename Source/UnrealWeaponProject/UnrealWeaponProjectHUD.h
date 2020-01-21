// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"	
#include "WeaponWidget.h"
#include "UnrealWeaponProjectHUD.generated.h"

UCLASS()
class AUnrealWeaponProjectHUD : public AHUD
{	
	GENERATED_BODY()

public:
	AUnrealWeaponProjectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> WeaponWidgetClass;

	UFUNCTION()
		void UpdateHealthCount(float Value);

	UFUNCTION()
		void PrintDamagePerShot(float Value);

	UFUNCTION()
		void PrintFireMode(FString Name);

	UFUNCTION()
		void PrintShotRate(float Value);


private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	UWeaponWidget* WeaponWidget;

};

