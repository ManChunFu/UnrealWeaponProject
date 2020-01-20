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
	UE_LOG(LogTemp, Warning, TEXT("currentPitch: %f"), currentPitch);
	UE_LOG(LogTemp, Warning, TEXT("currentYaw: %f"), currentYaw);
	if (TargetCharacter != nullptr && bCurrentlymoving)
	{
		//UE_LOG(LogTemp, Warning, TEXT("StuffY: %s"), bCurrentlymoving);
		//float x = RandPitch - currentPitch;
		//float y = RandYaw - currentYaw;
		
		if (PitchToAdd > 0.01f)
		{
			float PitchAdded = 0.5f;
			PitchToAdd -= PitchAdded;
			CurrentPitchOffset += PitchAdded;

			TargetCharacter->PitchCamera(-PitchAdded);
		}
		else if(CurrentPitchOffset > 0.01f)
		{
			float PitchRemoved = 0.5f;
			CurrentPitchOffset -= PitchRemoved;

			TargetCharacter->PitchCamera(PitchRemoved);
			if (CurrentPitchOffset < 0.01f)
			{

			}
		}
		


		//TargetCharacter->PitchCamera(y* rate*GetWorld()->GetDeltaSeconds());
		//currentYaw += rate * y * GetWorld()->GetDeltaSeconds();

		//UE_LOG(LogTemp, Warning, TEXT("StuffX: %f"), x);
		//UE_LOG(LogTemp, Warning, TEXT("StuffY: %f"), y);
		

		//if ((x >= -0.1f && x <= 0.1f )&& (y >= -0.1f && y <= 0.1f))
		//{
		//	TargetCharacter->RotateCamera(x);
		//	TargetCharacter->PitchCamera(y);
		//	
		//	
		//	bCurrentlymoving = false;
		//	//PrimaryComponentTick.SetTickFunctionEnable(false);
		//}
	}
	
	if (!bCurrentlymoving)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("False"));
		float x = RandPitch + currentPitch ;
		//float y = RandYaw + currentYaw ;

		TargetCharacter->RotateCamera((x *-1)* rate*GetWorld()->GetDeltaSeconds());
		currentPitch -=  x  *rate* GetWorld()->GetDeltaSeconds();

		//TargetCharacter->PitchCamera((y*-1)  * rate*GetWorld()->GetDeltaSeconds());
		//currentYaw -=   y *rate* GetWorld()->GetDeltaSeconds();

		/*if ((currentPitch >= -0.1f && currentPitch <= 0.1) && (currentYaw >= -0.1f && currentYaw <= 0.1f))
		{
			TargetCharacter->RotateCamera(currentPitch);
			TargetCharacter->PitchCamera(currentYaw);
			PrimaryComponentTick.SetTickFunctionEnable(false);
			UE_LOG(LogTemp, Warning, TEXT("currentPitch: %f"), currentPitch);
			UE_LOG(LogTemp, Warning, TEXT("currentYaw: %f"), currentYaw);
		}*/
	}
}


// Called every frame


void UCameraShakeComponent::DoCameraShake(AUnrealWeaponProjectCharacter* Character)
{

	if (Character != nullptr)
	{
		TargetCharacter = Character;

		PrimaryComponentTick.SetTickFunctionEnable(true);

		RandPitch = 10.f;
		PitchToAdd += 10.f;
		//RandYaw = FMath::RandRange(MinRandYaw, MaxRandYaw);

		bCurrentlymoving = true;
	}
	

	
	//startPitch += RandPitch * -1;
	//startYaw += RandYaw * -1;
}

