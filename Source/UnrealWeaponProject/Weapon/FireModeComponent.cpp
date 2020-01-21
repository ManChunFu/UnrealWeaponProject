// Fill out your copyright notice in the Description page of Project Settings.


#include "FireModeComponent.h"
#include "Components/AudioComponent.h"
#include "UnrealWeaponProject/UnrealWeaponProjectHUD.h"

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
			Weapon->TryAttack();
			NextAttackTime = GetWorld()->GetTimeSeconds() + (BurstDelay * NextAttackMargin);
			BurstCounter++;
			if (BurstCounter >= AttacksPerBurst)
			{
				bBursting = false;
				NextAttackTime = GetWorld()->GetTimeSeconds() - (AttacksPerBurst*BurstDelay) + (1/BurstsPerSecond)* NextAttackMargin;
				GetWorld()->GetTimerManager().ClearTimer(BurstHandle);
			}
		});

	UnrealWeaponProjectHUD = Cast<AUnrealWeaponProjectHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	/*EFireMode UseEnumValue = CurrentFireMode;
	PrintFireModeOnHUD(*GETENUMSTRING("EUsesEnum", UseEnumValue));*/
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
	if (Weapon->TryAttack())
	{
		switch (CurrentFireMode)
		{
		case EFireMode::FullAuto:
			NextAttackTime = GetWorld()->GetTimeSeconds() + (1.f / AutoAttacksPerSecond) * NextAttackMargin;
			break;

		case EFireMode::SemiAuto:
			NextAttackTime = GetWorld()->GetTimeSeconds() + (1.f / SemiAutoAttackPerSecond) * NextAttackMargin;
			break;

		default:
			break;
		}

		PlaySound(FireSoundCue);
	}
	else
	{
		StopSound();
	}
}

void UFireModeComponent::Burst()
{
	if (BurstDelegate.IsBound() && !bBursting && CanAttack_Implementation())
	{
		PlaySound(FireSoundCue);

		BurstCounter = 0;
		bBursting = true;
		GetWorld()->GetTimerManager().SetTimer(BurstHandle, BurstDelegate, BurstDelay, true, 0.f);
	}
	else
	{
		StopSound();
	}

}

void UFireModeComponent::Start()
{
	switch (CurrentFireMode)
	{
	case EFireMode::FullAuto:
		Attack();
		GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Attack, 1.f / AutoAttacksPerSecond, true);
		EFireMode UseEnumValue = EFireMode::FullAuto;
		PrintFireModeOnHUD(*GETENUMSTRING("EFireMode", UseEnumValue));
		PrintShotRateOnHUD(AutoAttacksPerSecond);
		break;


	case EFireMode::BurstFire:
		GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Burst, 1.f / BurstsPerSecond, true, 0.f);
		EFireMode UseEnumValue = EFireMode::BurstFire;
		PrintFireModeOnHUD(*GETENUMSTRING("EFireMode", UseEnumValue));
		PrintShotRateOnHUD(BurstsPerSecond);
		break;


	case EFireMode::SemiAuto:
		EFireMode UseEnumValue = EFireMode::SemiAuto;
		PrintFireModeOnHUD(*GETENUMSTRING("EFireMode", UseEnumValue));
		PrintShotRateOnHUD(SemiAutoAttackPerSecond);
		Attack();

		break;
	}

}

void UFireModeComponent::Stop()
{
	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}

bool UFireModeComponent::CanAttack_Implementation()
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

void UFireModeComponent::StopSound()
{
	if (SoundAudioComponent->IsPlaying())
	{
		SoundAudioComponent->Stop();
	}
}

void UFireModeComponent::PrintFireModeOnHUD(FString Name)
{
	if (UnrealWeaponProjectHUD)
	{
		UnrealWeaponProjectHUD->PrintFireMode(Name);
	}
}


void UFireModeComponent::PrintShotRateOnHUD(float Value)
{
	if (UnrealWeaponProjectHUD)
	{
		UnrealWeaponProjectHUD->PrintShotRate(Value);
	}
}

