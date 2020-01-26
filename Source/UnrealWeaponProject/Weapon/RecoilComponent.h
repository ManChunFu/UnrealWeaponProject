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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Current Recoil")
		/**The Current Maximum Recoil Value. 
		The Max Recoil number represents the maximum value that the "bullet" will deviate from a straight line*/
		float CurrentMaxRecoil = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Current Recoil")
		/**The Current Minimum Recoil Value.
		The Min Recoil number represents the minimum value that the "bullet" will deviate from a straight line*/
		float CurrentMinRecoil = 0.1f;


	// Current Decrease Rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Timer")
		/**How often the recoil timer will decrease the current Recoil value*/
		float DecreaseRate = 0.2f;


	// Current Recoil Add Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Add Amount")
		/**How much the Max recoil value should increase each time the gun is fired */
		float MaxRecoilAddAmount = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Add Amount")
		/**How much the Min recoil value should increase each time the gun is fired */
		float MinRecoilAddAmount = 0.5f;


	// Current Recoil Decrease Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Decrease Amount")
		/**How much the Max recoil value should decrease each time the timer ticks */
		float MaxRecoilDecreaseAmount = 0.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Decrease Amount")
		/**How much the Min recoil value should decrease each time the timer ticks */
		float MinRecoilDecreaseAmount = 0.25f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Limits")
		/**What the Max recoil value upper limit is, meaning what number it cant get HIGHER then*/
		float MaxRecoilUpLimit = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Limits")
		/**What the Min recoil value upper limit is, meaning what number it cant get HIGHER then*/
		float MinRecoilUpLimit = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Limits")
		/**What the Max recoil value lower limit is, meaning what number it cant get LOWER then*/
		float MaxRecoilLowLimit = 0.3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil|Limits")
		/**What the Min recoil value lower limit is, meaning what number it cant get LOWER then*/
		float MinRecoilLowLimit = 0.1f;




	UFUNCTION(BlueprintCallable)
		/** Calculates the recoil based on its values. Addrecoil determines if the recoil should increase each time its called*/
		void DoRecoil(bool bAddRecoil);


	UFUNCTION(BlueprintCallable)
		/** Increases CurrentRecoil values with given values*/
		void AddRecoil(float O_PitchToAdd, float O_YawToAdd);


	virtual void OnWeaponAttack_Implementation();

private:


	FTimerHandle Handle;
	FTimerDelegate TimerCallback;
	float Timer = 0;
	
};