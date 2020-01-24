// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"
#include "Engine/World.h"
#include "Weapon.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> EmptyMagazineSoundCueObject(TEXT("SoundCue'/Game/Audio/Sounds/Weapon_AssaultRifle/Stereo/AmmoEmptySound_Cue.AmmoEmptySound_Cue'"));
	if (EmptyMagazineSoundCueObject.Succeeded())
	{
		EmptyMagazineSoundCue = EmptyMagazineSoundCueObject.Object;
	}
	SoundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundAudioComponent"));
}


// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();
	Weapon = Cast<AWeapon>(GetOwner());
}

bool UAmmoComponent::Reload()
{
	if (MagazineAmmo >= MagazineSize || SpareAmmo <= 0)
	{
		return false;
	}
	if (bIsReloading == false)
	{
		bIsReloading = true;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UAmmoComponent::FinishReload, ReloadTime, false);
		UE_LOG(LogTemp, Warning, TEXT("Starting Reload"));
	}
	return true;
}


bool UAmmoComponent::CanAttack_Implementation()
{
	if (!bIsReloading)
	{
		if (MagazineAmmo > 0)
		{
			return true;
		}
		PlaySound(EmptyMagazineSoundCue);
	}
	return false;
}

void UAmmoComponent::OnWeaponAttack_Implementation()
{
	MagazineAmmo--;
}

void UAmmoComponent::FinishReload()
{	
	UE_LOG(LogTemp, Warning, TEXT("Finished Reload"));
	bIsReloading = false;

	// Enough Ammo to Fill Magazine
	if (MagazineAmmo + SpareAmmo >= MagazineSize)
	{
		SpareAmmo += MagazineAmmo;
		MagazineAmmo = MagazineSize;
		SpareAmmo -= MagazineSize;
		return;
	}
	// Little ammo left to top up magazine
	MagazineAmmo += SpareAmmo;
	SpareAmmo = 0;

}

void UAmmoComponent::PlaySound(USoundBase* SoundCue)
{
	if (SoundAudioComponent && SoundCue)
	{
		SoundAudioComponent->SetSound(SoundCue);
		SoundAudioComponent->Play(0.f);
	}
}




