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

		if (OriginalFov == -1)
		{
			OriginalFov = HolderCamera->FieldOfView;
		}

		if (HolderCamera->FieldOfView == OriginalFov)
		{
			HolderCamera->FieldOfView = ZoomedFoV;
		}
		else
		{
			HolderCamera->FieldOfView = OriginalFov;
		}
	}
}


void UScopeComponent::OnWeaponEquipped_Implementation(AActor* NewHolder)
{
	if (NewHolder->IsA<AUnrealWeaponProjectCharacter>())
	{
		HolderCamera = Cast<AUnrealWeaponProjectCharacter>(NewHolder)->GetFirstPersonCameraComponent();
	}
	else
	{
		HolderCamera = nullptr;
	}
}

void UScopeComponent::OnWeaponDropped_Implementation()
{
	if (HolderCamera)
	{
		HolderCamera->FieldOfView = OriginalFov;
	}
	HolderCamera = nullptr;
}

