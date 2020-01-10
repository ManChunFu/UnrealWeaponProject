// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponHitScanComponent.h"
#include "Math/RandomStream.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"

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

void UWeaponHitScanComponent::OnAttack(FVector StartTrace, FVector ForwardVector, bool bDebugLine)
{
	
	FVector EndTrace = ((ForwardVector * 2000.f) + StartTrace);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	
	if (bDebugLine)
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 5.f);
		UE_LOG(LogTemp, Warning, TEXT("Drawing Line"));
	}
	
	

	
}




