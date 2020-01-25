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
		float DecreaseRate = 0.2f;

	// Current Recoil Decrease Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxRecoilDecreaseAmount = 0.25f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinRecoilDecreaseAmount = 0.25f;

	// Current Recoil Add Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxRecoilAddAmount = 0.5f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinRecoilAddAmount = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxRecoilUpLimit = 3.f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinRecoilUpLimit = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxRecoilLowLimit = 0.03;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinRecoilLowLimit = 0.01f;




	UFUNCTION(BlueprintCallable)
		void DoRecoil(bool bAddRecoil);


	UFUNCTION(BlueprintCallable)
		void AddRecoil(float O_PitchToAdd, float O_YawToAdd);


	virtual void OnWeaponAttack_Implementation();

private:


	FTimerHandle Handle;
	FTimerDelegate TimerCallback;
	float Timer = 0;
	
};