// Fill out your copyright notice in the Description page of Project Settings.

#include "ScopeComponent.h"
#include "../UnrealWeaponProjectCharacter.h"
#include "Weapon.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"


// Sets default values for this component's properties
UScopeComponent::UScopeComponent()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> ZoomSoundCueObject(TEXT("SoundCue'/Game/Audio/SnaiperZoom_Cue.SnaiperZoom_Cue'"));
	if (ZoomSoundCueObject.Succeeded())
	{
		ZoomSoundCue = ZoomSoundCueObject.Object;
	}
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
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
		PlaySoundCue(ZoomSoundCue, 0.0f, 2.f);
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

void UScopeComponent::PlaySoundCue(USoundBase* SoundCue, float StartTime, float VolumMultiplier)
{
	if (AudioComponent && SoundCue)
	{
		AudioComponent->SetSound(SoundCue);
		AudioComponent->SetVolumeMultiplier(VolumMultiplier);
		AudioComponent->Play(StartTime);
	}
}

