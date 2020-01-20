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


// Called when the game starts


//void URecoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//
//	Timer += DeltaTime;
//
//	if (Timer >= DecreaseRate && bDecreseRecoilOverTime)
//	{
//		RecoilTimer();
//		Timer = 0;
//	}
//}

//void URecoilComponent::SetRecoilDecreaseRate(float MaxRecoilDecreaseAmount, float MinRecoilDecreaseAmount, float DecreaseRate)
//{
//	C_DecrRate = DecreaseRate;
//}
//
//void URecoilComponent::AddRecoil(float PlusMaxRecoil, float PlusMinRecoil)
//{
//	
//	
//}
//
//void URecoilComponent::SetCurrentRecoil(float MaxRecoil, float MinRecoil)
//{
//	CurrentMaxRecoil = MaxRecoil;
//	CurrentMinRecoil = MinRecoil;
//}

//void URecoilComponent::SetAllRecoilSettings(bool bReduceRecoilOverTime, float DecreaseRate,float MaxRecoilDecreaseAmount, float MinRecoilDecreaseAmount)
//{
//	bDecreseRecoilOverTime = bReduceRecoilOverTime;
//
//	
//
//	C_DecrRate = DecreaseRate;
//
//	
//
//	C_MaxRecDecrAmount = MaxRecoilDecreaseAmount;
//	C_MinRecDecrAmount = MinRecoilDecreaseAmount;
//
//	
//}


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


	/*if (bNegativeValue)
	{
		ActualRecoilX = FMath::RandRange(CurrentMaxRecoil, CurrentMinRecoil);
	}
	else
	{
		ActualRecoilX = FMath::RandRange(CurrentMaxRecoil * -1, CurrentMinRecoil * -1);
	}



	
	bNegativeValue = FMath::RandBool();
	if (bNegativeValue)
	{
		ActualRecoilY = FMath::RandRange(CurrentMaxRecoil, CurrentMinRecoil);
	}
	else
	{
		ActualRecoilY = FMath::RandRange(CurrentMaxRecoil * -1, CurrentMinRecoil * -1);
	}*/


	/*if (CurrentMaxRecoil < MaxRecoilUpLimit)
	{
		CurrentMaxRecoil += MaxRecoilAddAmount;
	}
	if (CurrentMinRecoil < MinRecoilUpLimit)
	{
		CurrentMinRecoil += MinRecoilAddAmount;
	}*/

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


//UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary")
//void URecoilComponent::GetCurrentRecoil(float& ActualRecoilX, float& ActualRecoilY, float& MaxRecoil, float& MinRecoil)
//{
//	MaxRecoil = CurrentMaxRecoil;
//	MinRecoil = CurrentMinRecoil;
//	
//	
//	bool bNegativeValue = FMath::RandBool();
//	if (bNegativeValue)
//	{
//		ActualRecoilX = FMath::RandRange(CurrentMaxRecoil, CurrentMinRecoil);	
//	}
//	else
//	{
//		ActualRecoilX = FMath::RandRange(CurrentMaxRecoil*-1, CurrentMinRecoil*-1);	
//	}
//
//
//	bNegativeValue = FMath::RandBool();
//	if (bNegativeValue)
//	{
//		ActualRecoilY = FMath::RandRange(CurrentMaxRecoil, CurrentMinRecoil);
//	}
//	else
//	{
//		ActualRecoilY = FMath::RandRange(CurrentMaxRecoil * -1, CurrentMinRecoil * -1);
//	}
//	
//}

//void URecoilComponent::RecoilTimer()
//{
//	CurrentMaxRecoil -= MaxRecoilDecreaseAmount;
//	CurrentMinRecoil -= MinRecDecreaseAmount;
//
//}
