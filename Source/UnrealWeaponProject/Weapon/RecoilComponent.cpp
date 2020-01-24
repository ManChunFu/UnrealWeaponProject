// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
// Sets default values for this component's properties
URecoilComponent::URecoilComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void URecoilComponent::BeginPlay()
{
	Super::BeginPlay();
	TimerCallback.BindLambda([this]()
		{
			if (this->CurrentMaxRecoil > this->MaxRecoilLowLimit)
			{
				this->CurrentMaxRecoil -= this->MaxRecoilDecreaseAmount;
			}
			if (this->CurrentMinRecoil > this->MinRecoilLowLimit)
			{
				this->CurrentMinRecoil -= this->MinRecoilDecreaseAmount;
			}

			if (this->CurrentMaxRecoil <= this->MaxRecoilLowLimit && this->CurrentMinRecoil <= this->MinRecoilLowLimit)
			{
				GetWorld()->GetTimerManager().ClearTimer(Handle);
			}
			UE_LOG(LogTemp, Warning, TEXT("Timer Tick"));
		});

	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, DecreaseRate, true);


}

void URecoilComponent::DoRecoil(float& ActualRecoilX, float& ActualRecoilY)
{
	UE_LOG(LogTemp, Warning, TEXT("MaxRecoil %f"), CurrentMaxRecoil);
	UE_LOG(LogTemp, Warning, TEXT("MinRecoil %f"), CurrentMinRecoil);
	bool bNegativeValue = FMath::RandBool();
	float a = FMath::RandRange(0.f, 1.f) * 2.f * PI;
	float r = FMath::RandRange(CurrentMinRecoil,CurrentMaxRecoil) * sqrt(FMath::RandRange(0.f, 1.f));

	ActualRecoilX = r * cosf(a);
	ActualRecoilY = r * sinf(a);




	if (!GetWorld()->GetTimerManager().IsTimerActive(Handle))
	{
		GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, DecreaseRate, true);
	}


	UE_LOG(LogTemp, Warning, TEXT("MaxRecoil %f"), CurrentMaxRecoil);
	UE_LOG(LogTemp, Warning, TEXT("MinRecoil %f"), CurrentMinRecoil);
}

void URecoilComponent::AddRecoil(float MaxRecoilToAdd, float MinRecoildToAdd)
{
	CurrentMaxRecoil += MaxRecoilToAdd;
	CurrentMinRecoil += MinRecoildToAdd;
}



