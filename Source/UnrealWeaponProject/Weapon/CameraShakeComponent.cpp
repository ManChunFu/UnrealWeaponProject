// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShakeComponent.h"
#include "../UnrealWeaponProjectCharacter.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UCameraShakeComponent::UCameraShakeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraShakeComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.SetTickFunctionEnable(false);
	// ...
	
}

void UCameraShakeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetCharacter != nullptr)
	{	
		timer -= DeltaTime;
		if (PitchToAdd < -0.5f || PitchToAdd > 0.5f)
		{
			float PitchAdded = PitchAddSpeed;
			PitchToAdd += PitchAdded;
			CurrentPitchOffset += PitchAdded;
			float r = 0.2;
			TargetCharacter->PitchCamera(PitchAdded);
		}
		else if((CurrentPitchOffset < -0.5f || CurrentPitchOffset > 0.5f )&& timer <= 0 && bRecoildReset)		
		{			
			CurrentPitchOffset += PitchRemovedRate;
			TargetCharacter->PitchCamera(PitchRemovedRate);
		}

		if (YawToAdd < -0.4f || YawToAdd > 0.4f)
		{
			float sign = YawToAdd > 0 ? 1 : -1;
			float YawAdded = YawAddSpeed * sign;
			YawToAdd -= YawAdded;
			CurrentYawOffset += YawAdded;
			
			TargetCharacter->RotateCamera(YawAdded);
		}
		else if ((CurrentYawOffset < -0.4f || CurrentYawOffset > 0.4f) && timer <= 0 && bRecoildReset)
		{
			float sign = CurrentYawOffset > 0 ? 1 : -1;
			float YawRemoved = YawRemoveRate * sign;
			
			CurrentYawOffset -= YawRemoved;

			TargetCharacter->RotateCamera(-YawRemoved );
		}
	}
}


void UCameraShakeComponent::DoCameraShake(AUnrealWeaponProjectCharacter* Character)
{

	if (Character != nullptr)
	{
		TargetCharacter = Character;
		PrimaryComponentTick.SetTickFunctionEnable(true);

		PitchToAdd += FMath::RandRange(MinRandPitch, MaxRandPitch);
		YawToAdd += FMath::RandRange(MinRandYaw, MaxRandYaw);
		timer = TimeUntillReset;
		//UE_LOG(LogTemp, Warning, TEXT("PitchToAdd: %f"), PitchToAdd);
	}
}

