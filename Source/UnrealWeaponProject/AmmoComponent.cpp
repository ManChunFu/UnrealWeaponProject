// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAmmoComponent::OnAttack()
{

}

void UAmmoComponent::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading"));
	MagazineAmmo = MagazineSize;
}

bool UAmmoComponent::DecreaseAmmo(int32 Amount)
{
	if (MagazineAmmo >= Amount)
	{
		MagazineAmmo -= Amount;
		UE_LOG(LogTemp, Warning, TEXT("Ammo Left %d"), MagazineAmmo);
		return true;
	}
	Reload();
	return false;
}


