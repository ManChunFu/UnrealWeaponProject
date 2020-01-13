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

void UFireModeComponent::BurstFire(float RateOfFire, AWeapon* Weapon, int32 AttacksPerBurst)
{
	GetWorld()->GetTimerManager().SetTimer(FireHandle, Weapon, &AWeapon::Attack, RateOfFire, true);
}

void UFireModeComponent::Burst(AWeapon* Weapon)
{

}

void UFireModeComponent::Stop()
{
	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}

