// Fill out your copyright notice in the Description page of Project Settings.


#include "FireModeComponent.h"

// Sets default values for this component's properties
UFireModeComponent::UFireModeComponent()
{
	AllowedFireModes.Add(EFireMode::FM_SemiAuto);
	CurrentFireMode = EFireMode::FM_SemiAuto;
}

void UFireModeComponent::BeginPlay()
{
	Super::BeginPlay();
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
		case EFireMode::FM_AutoAttack:
			NextAttackTime = GetWorld()->GetTimeSeconds() + (1.f / AutoAttacksPerSecond) * 0.95f;
			break;

		case EFireMode::FM_SemiAuto:
			NextAttackTime = GetWorld()->GetTimeSeconds() + (1.f / SemiAutoAttackPerSecond) * 0.95f;
			break;

		default :
			break;
		}
	}
}

void UFireModeComponent::Burst()
{
	//Burst is special, Last attack time should count from only the first bullet so special case is set up for that.
	if (BurstDelegate.IsBound() && !bBursting && CanAttack())
	{
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
	case EFireMode::FM_AutoAttack:
		Attack();
		GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Attack, 1.f / AutoAttacksPerSecond, true);
		break;


	case EFireMode::FM_BurstFire:
		GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Burst, 1.f / BurstsPerSecond, true, 0.f);
		break;


	case EFireMode::FM_SemiAuto:
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

