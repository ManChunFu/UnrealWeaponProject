// Fill out your copyright notice in the Description page of Project Settings.


#include "FireModeComponent.h"
#include "Components/AudioComponent.h"
#include "AmmoComponent.h"

// Sets default values for this component's properties
UFireModeComponent::UFireModeComponent()
{
	SoundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundAudioComponent"));
}

void UFireModeComponent::BeginPlay()
{
	Super::BeginPlay();
	if (AllowedFireModes.Num() <= 0)
	{
		AllowedFireModes.Add(CurrentFireMode);
		UE_LOG(LogTemp, Warning, TEXT("No assigned fire modes for weapon : %s"), *GetOwner()->GetName());

	}
	Weapon = Cast<AWeapon>(GetOwner());
	BurstDelegate.BindLambda([=]
		{
			Weapon->Attack();
			BurstCounter++;
			if (BurstCounter >= AttacksPerBurst)
			{
				bBursting = false;
				GetWorld()->GetTimerManager().ClearTimer(BurstHandle);
			}
		});
	
	//AmmoComponent = Cast<UAmmoComponent>(GetOwner());
}

void UFireModeComponent::ChangeFireMode()
{
	int32 Index = AllowedFireModes.Find(CurrentFireMode);
	CurrentFireMode = AllowedFireModes[(Index + 1) % AllowedFireModes.Num()];
}


void UFireModeComponent::BurstFire()
{
	Burst();
	GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Burst, 1.f / BurstsPerSecond, true);

}

void UFireModeComponent::Attack()
{
	if (CanAttack())
	{
		Weapon->Attack();

		switch (CurrentFireMode)
		{
		case EFireMode::FullAuto:
			NextAttackTime = GetWorld()->GetTimeSeconds() + (1.f / AutoAttacksPerSecond) * 0.95f;
			break;

		case EFireMode::SemiAuto:
			NextAttackTime = GetWorld()->GetTimeSeconds() + (1.f / SemiAutoAttackPerSecond) * 0.95f;
			break;

		default :
			break;
		}

		// play firing sound or play empty magazine sound
		//if (AmmoComponent)
		//{
		//	if (AmmoComponent->MagazineAmmo > 0)
		//	{
				PlaySound(FireSoundCue);
		//	}
		//	else
		//	{
		//		PlaySound(EmptyMagazineSoundCue);
		//	}
		//}
	}
}

void UFireModeComponent::Burst()
{
	//Burst is special, Last attack time should count from only the first bullet so special case is set up for that.
	if (BurstDelegate.IsBound() && !bBursting && CanAttack())
	{
		// play firing sound or play empty magagzine sound
		/*if (AmmoComponent)
		{
			if (AmmoComponent->MagazineAmmo > 0)
			{
			*/	PlaySound(FireSoundCue);
		//	}
		//	else
		//	{
		//		PlaySound(EmptyMagazineSoundCue);
		//	}
		//}

		BurstCounter = 0;
		bBursting = true;
		NextAttackTime = GetWorld()->GetTimeSeconds() + (1.f/BurstsPerSecond)*0.95f;
		GetWorld()->GetTimerManager().SetTimer(BurstHandle, BurstDelegate, BurstDelay, true, 0.f);
	}
}

void UFireModeComponent::Start()
{

	switch (CurrentFireMode)
	{
	case EFireMode::FullAuto:
		Attack();
		GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Attack, 1.f / AutoAttacksPerSecond, true);
		break;


	case EFireMode::BurstFire:
		GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Burst, 1.f / BurstsPerSecond, true, 0.f);
		break;


	case EFireMode::SemiAuto:
		Attack();

		break;
	}

}

void UFireModeComponent::Stop()
{
	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}

bool UFireModeComponent::CanAttack()
{
	return NextAttackTime <= GetWorld()->GetTimeSeconds();
}

void UFireModeComponent::PlaySound(USoundBase* SoundCue)
{
	if (SoundAudioComponent && SoundCue)
	{
		SoundAudioComponent->SetSound(SoundCue);
		SoundAudioComponent->Play(0.f);
	}
}

