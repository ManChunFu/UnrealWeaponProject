// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.h"
#include "RecoilComponent.h"
#include "CameraShakeComponent.h"
#include "../MathHelperFunctions.h"

// Sets default values for this component's properties
UHitscanComponent::UHitscanComponent()
{
}


// Called when the game starts
void UHitscanComponent::BeginPlay()
{
	Super::BeginPlay();

	BulletsPerShot = Cast<AWeapon>(GetOwner())->BulletsPerShot;


	auto RecoilComp = GetOwner()->GetComponentByClass(URecoilComponent::StaticClass());
	if (RecoilComp)
	{
		Recoil = Cast<URecoilComponent>(RecoilComp);
	}

}

TArray<FHitResult> UHitscanComponent::Fire(float InaccuracyZ, float InaccuracyY, bool bDebugLine)
{

	TArray<FHitResult> Hits;
	for (int i = 0; i < BulletsPerShot; i++)
	{
		float YOnCircle, ZOnCircle;
		UMathHelperFunctions::GetRandomPointOnCircle(ZOnCircle, YOnCircle);
		FTransform SpawnTransform;

		SpawnTransform = Cast<AWeapon>(GetOwner())->GetSpawnPoint();

		FQuat ZRotation(FVector::UpVector, ZOnCircle * InaccuracyZ * PI / 180.f);
		FQuat YRotation(FVector::RightVector, YOnCircle * InaccuracyY * PI / -180.f);
		SpawnTransform.SetRotation(SpawnTransform.GetRotation() * ZRotation * YRotation);
		FVector TraceStart = SpawnTransform.GetLocation();
		FVector TraceEnd = SpawnTransform.GetLocation() + SpawnTransform.GetRotation().GetForwardVector() * 10000.f;

		FCollisionQueryParams TraceParams;
		FHitResult OutHit;

		if (GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
		{
			UGameplayStatics::ApplyDamage(OutHit.GetActor(), Damage, GetOwner()->GetInstigatorController(), GetOwner(), nullptr);
		}



		if (bDebugLine)
		{
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.f);
		}
		Hits.Add(OutHit);
	}

	return Hits;
}

void UHitscanComponent::OnWeaponAttack_Implementation()
{
	if (Recoil)
	{
		Fire(Recoil->CurrentMaxRecoil, Recoil->CurrentMaxRecoil, bDrawDebugLine);
		return;
	}

	
	UE_LOG(LogTemp, Warning, TEXT("No RecoilComp found on HitScan, using default numbers."));
	Fire(0.f, 0.f, true);
}

