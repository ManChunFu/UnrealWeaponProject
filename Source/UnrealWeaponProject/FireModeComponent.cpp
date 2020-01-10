// Fill out your copyright notice in the Description page of Project Settings.


#include "FireModeComponent.h"

// Sets default values for this component's properties
UFireModeComponent::UFireModeComponent()
{

}

void UFireModeComponent::AutoFire(float RateOfFire, AWeapon* Weapon)
{
	GetWorld()->GetTimerManager().SetTimer(FireHandle, Weapon, &AWeapon::Attack, RateOfFire, true);
	Weapon->Attack();
}

void UFireModeComponent::BurstFire(float RateOfFire, int32 AttacksPerBurst)
{
}

void UFireModeComponent::Stop()
{
	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}

