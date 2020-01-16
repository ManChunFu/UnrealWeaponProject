// Fill out your copyright notice in the Description page of Project Settings.


#include "FireModeComponent.h"

// Sets default values for this component's properties
UFireModeComponent::UFireModeComponent()
{
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

void UFireModeComponent::AutoFire()
{

	GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Attack, 1.f / AttacksPerSecond, true);
}

void UFireModeComponent::BurstFire()
{
	Burst();
	GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &UFireModeComponent::Burst, 1.f / AttacksPerSecond, true);

}

void UFireModeComponent::Attack()
{
	if (CanAttack())
	{
		Weapon->Attack();
		LastAttackTime = GetWorld()->GetTimeSeconds();
	}
}

void UFireModeComponent::Burst()
{
	//Burst is special, Last attack time should count from only the first bullet so special case is set up for that.
	if (BurstDelegate.IsBound() && !bBursting && CanAttack())
	{
		BurstCounter = 0;
		bBursting = true;
		BurstDelegate.Execute();
		LastAttackTime = GetWorld()->GetTimeSeconds();
		GetWorld()->GetTimerManager().SetTimer(BurstHandle, BurstDelegate, BurstDelay, true);
	}
}

void UFireModeComponent::Stop()
{
	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}

bool UFireModeComponent::CanAttack()
{
	// Give a little extra room for attack so no attacks get missed
	return (1.f / AttacksPerSecond)*0.95f + LastAttackTime <= GetWorld()->GetTimeSeconds();
}

