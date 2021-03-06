// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnrealWeaponProjectHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AUnrealWeaponProjectHUD::AUnrealWeaponProjectHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void AUnrealWeaponProjectHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X-8),
										   (Center.Y)-8);

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void AUnrealWeaponProjectHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponWidgetClass)
	{
		WeaponWidget = CreateWidget<UWeaponWidget>(GetWorld(), WeaponWidgetClass);
		if (WeaponWidget)
		{
			WeaponWidget->AddToViewport();
		}
	}
}

void AUnrealWeaponProjectHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AUnrealWeaponProjectHUD::UpdateHealthCount(float Value)
{
	if (WeaponWidget)
	{
		WeaponWidget->UpdateHealthCout(Value);
	}
}

void AUnrealWeaponProjectHUD::PrintDamagePerShot(float Value, FString Multiplier)
{
	if (WeaponWidget)
	{
		WeaponWidget->PrintDamagePerShot(Value, Multiplier);
	}
}

void AUnrealWeaponProjectHUD::PrintFireMode(FString Name)
{
	if (WeaponWidget)
	{
		WeaponWidget->PrintFireMode(Name);
	}
}

void AUnrealWeaponProjectHUD::PrintShotRate(float Value)
{
	if (WeaponWidget)
	{
		WeaponWidget->PrintShotRate(Value);
	}
}






