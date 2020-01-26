// Fill out your copyright notice in the Description page of Project Settings.

#include "ScopeComponent.h"
#include "../UnrealWeaponProjectCharacter.h"
#include "Weapon.h"

// Sets default values for this component's properties
UScopeComponent::UScopeComponent()
{
}


// Called when the game starts
void UScopeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UScopeComponent::Zoom()
{
	if (HolderCamera)
	{
		if (bIsZoomedIn)
		{
			HolderCamera->FieldOfView = OriginalFov;
			bIsZoomedIn = false;
		}
		else
		{
			HolderCamera->FieldOfView = ZoomedFoV;
			bIsZoomedIn = true;
		}
	}
}


void UScopeComponent::OnWeaponEquipped_Implementation(AActor* NewHolder)
{
	if (NewHolder->IsA<AUnrealWeaponProjectCharacter>())
	{
		HolderCamera = Cast<AUnrealWeaponProjectCharacter>(NewHolder)->GetFirstPersonCameraComponent();
		OriginalFov = HolderCamera->FieldOfView;
	}
	else
	{
		HolderCamera = nullptr;
	}
}

void UScopeComponent::OnWeaponDropped_Implementation()
{
	if (bIsZoomedIn)
	{
		HolderCamera->FieldOfView = OriginalFov;
	}
	HolderCamera = nullptr;
	OriginalFov = -1;
}

