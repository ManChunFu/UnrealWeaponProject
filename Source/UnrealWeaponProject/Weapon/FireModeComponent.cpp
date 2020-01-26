// Fill out your copyright notice in the Description page of Project Settings.


#include "FireModeComponent.h"
#include "Components/AudioComponent.h"
#include "UnrealWeaponProject/UnrealWeaponProjectHUD.h"

// Sets default values for this component's properties
UFireModeComponent::UFireModeComponent()
{
	AllowedFireModes.Add(EFireMode::FullAuto);
}

void UFireModeComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentFireMode = AllowedFireModes[0];

	Weapon = Cast<AWeapon>(GetOwner());
	BurstDelegate.BindLambda([=]
		{
			if (!Weapon->TryAttack())
			{
				GetWorld()->GetTimerManager().ClearTimer(BurstHandle);
				bBursting = false;
			}

			BurstCounter++;
			if (BurstCounter >= AttacksPerBurst)
			{
				bBursting = false;
				NextAttackTime = GetWorld()->GetTimeSeconds() - ((AttacksPerBurst * BurstDelay) + (1 / BurstsPerSecond) * NextAttackMargin);
				GetWorld()->GetTimerManager().ClearTimer(BurstHandle);
			}
		});

}

void UFireModeComponent::ChangeFireMode()
{
	int32 Index = AllowedFireModes.Find(CurrentFireMode);
	CurrentFireMode = AllowedFireModes[(Index + 1) % AllowedFireModes.Num()];
	bBursting = false;
	GetWorld()->GetTimerManager().ClearTimer(BurstHandle);
	Stop();

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
	}
	else
	{
		Stop();
	}
}

void UFireModeComponent::Burst()
{
	if (BurstDelegate.IsBound() && !bBursting && CanAttack_Implementation())
	{
		BurstCounter = 0;
		bBursting = true;
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
		PrintShotRateOnHUD(AutoAttacksPerSecond);
		break;


	case EFireMode::BurstFire:
		if (!bBursting)
		{
			Burst();
			PrintShotRateOnHUD(BurstsPerSecond);
		}
		GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Burst, 1.f / BurstsPerSecond, true);
		break;


	case EFireMode::SemiAuto:
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


void UFireModeComponent::PrintShotRateOnHUD(float Value)
{
	AUnrealWeaponProjectHUD* UnrealWeaponProjectHUD = Cast<AUnrealWeaponProjectHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (UnrealWeaponProjectHUD)
	{
		UnrealWeaponProjectHUD->PrintShotRate(Value);
	}
}

