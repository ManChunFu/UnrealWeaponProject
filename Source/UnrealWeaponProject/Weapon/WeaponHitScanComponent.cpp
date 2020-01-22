// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponHitScanComponent.h"
#include "Math/RandomStream.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "../MathHelperFunctions.h"
#include "Weapon.h"

// Sets default values for this component's properties
UWeaponHitScanComponent::UWeaponHitScanComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponHitScanComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FHitResult UWeaponHitScanComponent::OnAttack(float InaccuracyZ, float InaccuracyY, bool bDebugLine)
{
	float YOnCircle, ZOnCircle;
	UMathHelperFunctions::GetRandomPointOnCircle(ZOnCircle, YOnCircle);
	FTransform SpawnTransform;

	SpawnTransform = Cast<AWeapon>(GetOwner())->GetSpawnPoint();
	
	FQuat ZRotation(FVector::UpVector, ZOnCircle * InaccuracyZ * PI / 180.f);
	FQuat YRotation(FVector::RightVector, YOnCircle * InaccuracyY * PI / -180.f);
	SpawnTransform.SetRotation(SpawnTransform.GetRotation() * ZRotation * YRotation);
	FVector TraceStart = SpawnTransform.GetLocation();
	FVector TraceEnd = SpawnTransform.GetLocation() + SpawnTransform.GetRotation().GetForwardVector()*10000.f;

	FCollisionQueryParams TraceParams;
	FHitResult OutHit;
	GetWorld()->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
	if (bDebugLine)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 5.f);
	}


	return OutHit;
	
	

	
}




