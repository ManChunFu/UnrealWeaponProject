// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{

}


// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()) { UE_LOG(LogTemp, Warning, TEXT("We are owned by: %s"), *GetOwner()->GetFName().ToString()); }
}

void UAmmoComponent::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading"));

	// Magazine is Full or 0 Spare Ammo
	if (MagazineAmmo >= MagazineSize && SpareAmmo <= 0)
	{
		return;
	}

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

bool UAmmoComponent::DecreaseAmmo(int32 Amount)
{
	if (MagazineAmmo >= Amount)
	{
		MagazineAmmo -= Amount;
		UE_LOG(LogTemp, Warning, TEXT("Ammo in mag %d"), MagazineAmmo);
		UE_LOG(LogTemp, Warning, TEXT("Ammo in bag %d"), SpareAmmo);
		return true;
	}
	Reload();
	return false;
}


