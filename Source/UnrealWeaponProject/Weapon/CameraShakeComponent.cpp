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
		if (CurrentPitchToAdd < -0.5f || CurrentPitchToAdd > 0.5f)
		{
			float PitchAdded = PitchAddSpeed;
			CurrentPitchToAdd += PitchAdded;
			CurrentPitchOffset += PitchAdded;
			
			TargetCharacter->PitchCamera(PitchAdded);
			
		}
		else if((CurrentPitchOffset < -0.5f || CurrentPitchOffset > 0.5f )&& timer <= 0 && bRecoildReset)		
		{			
			CurrentPitchOffset += PitchRemovedRate;	
			TargetCharacter->PitchCamera(PitchRemovedRate);
			
		}
		else if ((CurrentPitchOffset >= -0.5f && CurrentPitchOffset <= 0.5f) || !bRecoildReset)
		{
			bPitchDone = true;
		}


		if (CurrentYawToAdd < -0.4f || CurrentYawToAdd > 0.4f)
		{
			float sign = YawToAdd > 0 ? 1 : -1;
			float YawAdded = YawAddSpeed * sign;
			CurrentYawToAdd -= YawAdded;
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
		else if ((CurrentYawOffset >= -0.4f && CurrentYawOffset <= 0.4f) || !bRecoildReset)
		{
			bYawDone = true;
		}
		

		if (bPitchDone && bYawDone)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Turning Off Timer"));
			PrimaryComponentTick.SetTickFunctionEnable(false);
		}
	}
}


void UCameraShakeComponent::DoCameraShake(float O_PitchToAdd, float O_YawToAdd)
{
	if (Holder != nullptr)
	{
		
		CurrentPitchToAdd = O_PitchToAdd;
		CurrentYawToAdd = O_YawToAdd;
	
		TargetCharacter = Cast<AUnrealWeaponProjectCharacter>(Holder);
		bPitchDone = false;
		bYawDone = false;	
		PrimaryComponentTick.SetTickFunctionEnable(true);	
		timer = TimeUntillReset;
	}
}

void UCameraShakeComponent::ActivateCameraShake()
{
	PrimaryComponentTick.SetTickFunctionEnable(true);
	timer = TimeUntillReset;
}

void UCameraShakeComponent::OnWeaponAttack_Implementation()
{
	DoCameraShake(PitchToAdd, YawToAdd);
}

void UCameraShakeComponent::OnWeaponEquipped_Implementation(AActor* NewHolder)
{
	Holder = NewHolder;
}

void UCameraShakeComponent::OnWeaponDropped_Implementation()
{
	Holder = nullptr;
}


