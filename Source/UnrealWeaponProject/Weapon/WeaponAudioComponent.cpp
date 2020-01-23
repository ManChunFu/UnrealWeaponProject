// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAudioComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UWeaponAudioComponent::UWeaponAudioComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundBase> WeaponEquippedSoundCueObject(TEXT("SoundCue'/Game/Audio/Sounds/Weapon_AssaultRifle/Stereo/AssaultRifle_Equip_Stereo_Cue.AssaultRifle_Equip_Stereo_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundBase> WeaponDropppedSoundCueObject(TEXT("SoundCue'/Game/Audio/WeaponDropped_Cue.WeaponDropped_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundBase> FireSoundCueObject(TEXT("SoundCue'/Game/Audio/GunFire_Cue.GunFire_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundBase> ReloadSoundCueObject(TEXT("SoundCue'/Game/Audio/Sounds/Weapon_AssaultRifle/Stereo/AssaultRifle_Reload_Stereo_Cue.AssaultRifle_Reload_Stereo_Cue'"));

	if (WeaponEquippedSoundCueObject.Succeeded())
	{
		WeaponEquippedSoundCue = WeaponEquippedSoundCueObject.Object;
	}

	if (WeaponDropppedSoundCueObject.Succeeded())
	{
		WeaponDroppedSoundCue = WeaponDropppedSoundCueObject.Object;
	}

	if (FireSoundCueObject.Succeeded())
	{
		FireSoundCue = FireSoundCueObject.Object;
	}

	if (ReloadSoundCueObject.Succeeded())
	{
		ReloadSoundCue = ReloadSoundCueObject.Object;
	}

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}


// Called when the game starts
void UWeaponAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UWeaponAudioComponent::OnWeaponEquipped_Implementation(AActor* NewHolder)
{
	if (!bHasPlayed)
	{
		bHasPlayed = true;
		PlaySound(WeaponEquippedSoundCue, 0.f);
	}
}

void UWeaponAudioComponent::OnWeaponAttack_Implementation()
{
	PlaySound(FireSoundCue, 0.f);
}

void UWeaponAudioComponent::OnWeaponDropped_Implementation()
{
	bHasPlayed = false;
	PlaySound(WeaponDroppedSoundCue, 0.f);
}

void UWeaponAudioComponent::OnWeaponReload_Implementation()
{
	PlaySound(ReloadSoundCue, 0.f);
}

void UWeaponAudioComponent::PlaySound(USoundBase* SoundCue, float StartTime)
{
	if (AudioComponent && SoundCue)
	{
		AudioComponent->SetSound(SoundCue);
		AudioComponent->Play(0.0f);
	}
}

void UWeaponAudioComponent::StopSound()
{
	if (AudioComponent && AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}

}




