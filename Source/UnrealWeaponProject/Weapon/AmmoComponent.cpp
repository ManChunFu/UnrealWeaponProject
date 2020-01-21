// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"
#include "Engine/World.h"
#include "Weapon.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{
	SoundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundAudioComponent"));

}


// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();
	Weapon = Cast<AWeapon>(GetOwner());

}

void UAmmoComponent::Reload()
{
	if (MagazineAmmo >= MagazineSize || SpareAmmo <= 0)
	{
		return;
	}
	if (bIsReloading == false)
	{
		bIsReloading = true;

		 //play reload sound effect
		PlaySound(ReloadSoundCue);

		Weapon->SuspendedFromAttack++;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UAmmoComponent::FinishReload, ReloadTime, false);
		UE_LOG(LogTemp, Warning, TEXT("Starting Reload"));
	}

}


bool UAmmoComponent::CanAttack_Implementation()
{
	return MagazineAmmo > 0 && !bIsReloading;
}

void UAmmoComponent::OnWeaponAttack_Implementation()
{
	MagazineAmmo--;
}

void UAmmoComponent::FinishReload()
{	
	UE_LOG(LogTemp, Warning, TEXT("Finished Reload"));
	Weapon->SuspendedFromAttack--;
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




