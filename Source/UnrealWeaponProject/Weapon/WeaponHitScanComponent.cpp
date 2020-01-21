// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponHitScanComponent.h"
#include "Math/RandomStream.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "GameFramework/Actor.h"
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

FHitResult UWeaponHitScanComponent::OnAttack(FVector StartTrace, FVector ForwardVector,float InaccuracyZ, float InaccuracyY, bool bDebugLine)
{
	ForwardVector.Z += InaccuracyZ;
	ForwardVector.Y += InaccuracyY;
	FVector EndTrace = ((ForwardVector * 2000.f) + StartTrace);
	FCollisionQueryParams TraceParams;
	FHitResult testwhatever;
	GetWorld()->LineTraceSingleByChannel(testwhatever, StartTrace, EndTrace, ECC_Visibility, TraceParams);
	//UE_LOG(LogTemp, Warning, TEXT("StartTrace: %s"), StartTrace.ToString());
	if (bDebugLine)
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 5.f);
		UE_LOG(LogTemp, Warning, TEXT("Drawing Line"));
	}


	return testwhatever;
	
	

	
}




