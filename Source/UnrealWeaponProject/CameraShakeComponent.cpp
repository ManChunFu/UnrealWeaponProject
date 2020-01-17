// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShakeComponent.h"
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
		TargetCharacter->RotateCamera(rate * GetWorld()->GetDeltaSeconds());
		TargetCharacter->PitchCamera(rate * GetWorld()->GetDeltaSeconds());
		
		timer += GetWorld()->GetDeltaSeconds();
		if (timer >= 2.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Stuff"));
			PrimaryComponentTick.SetTickFunctionEnable(false);
			timer = 0;
		}
	}
}


// Called every frame


void UCameraShakeComponent::DoCameraShake(AUnrealWeaponProjectCharacter* Character)
{
	TargetCharacter = Character;

	
	PrimaryComponentTick.SetTickFunctionEnable(true);
	
	

	RandPitch = FMath::RandRange(MinRandPitch, MaxRandPitch);
	RandYaw = FMath::RandRange(MinRandYaw, MaxRandYaw);

	//startPitch += RandPitch * -1;
	//startYaw += RandYaw * -1;
}

