// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponentInterface.h"
#include "RecoilComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALWEAPONPROJECT_API URecoilComponent : public UActorComponent, public IWeaponComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URecoilComponent();

protected:
	virtual void BeginPlay() override;
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

public:

	bool bDecreseRecoilOverTime = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float CurrentMaxRecoil = 0.03f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float CurrentMinRecoil = 0.01f;

	// Current Decrease Rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float DecreaseRate = 1.f;

	// Current Recoil Decrease Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxRecoilDecreaseAmount = 0.002f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinRecoilDecreaseAmount = 0.002f;

	// Current Recoil Add Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxRecoilAddAmount = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinRecoilAddAmount = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxRecoilUpLimit = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinRecoilUpLimit = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxRecoilLowLimit = 0.03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinRecoilLowLimit = 0.01f;


	//UFUNCTION(BlueprintCallable)
		//void SetRecoilDecreaseRate(float MaxRecoilDecreaseAmount, float MinRecoilDecreaseAmount, float DecreaseRate);

	//UFUNCTION(BlueprintCallable)
		//void AddRecoil(float PlusMaxRecoil, float PlusMinRecoil);

	//UFUNCTION(BlueprintCallable)	
		//void SetCurrentRecoil( float MaxRecoil, float MinRecoil);

	//UFUNCTION(BlueprintCallable)
		//void SetAllRecoilSettings(bool bReduceRecoilOverTime, float DecreaseRate, float MaxRecoilDecreaseAmount, float MinRecoilDecreaseAmount);


	UFUNCTION(BlueprintCallable)
		void DoRecoil(float& ActualRecoilX, float& ActualRecoilY);


	UFUNCTION(BlueprintCallable)
		void AddRecoil(float MaxRecoilToAdd, float MinRecoildToAdd);
	//UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary") 
		//void GetCurrentRecoil(float& ActualRecoilX, float& ActualRecoilY, float& MaxRecoil, float& MinRecoil);



private:


	FTimerHandle Handle;
	FTimerDelegate TimerCallback;
	float Timer = 0;
	//void RecoilTimer();
};