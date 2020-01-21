// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "../UnrealWeaponProjectCharacter.h"
#include "CameraShakeComponent.generated.h"
class UInputComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALWEAPONPROJECT_API UCameraShakeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraShakeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	

	
		float timer = 0.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		float TimeUntillReset = 1.f;

	

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float MaxRandYaw = 2.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float MinRandYaw = -2.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float MaxRandPitch = 5.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float MinRandPitch = 4.f;

   
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test") 
			bool bRecoildReset = true;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float PitchAddSpeed = -1.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float YawAddSpeed = 1.f;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")	
			float PitchRemovedRate = 0.5f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float YawRemoveRate = 0.5f;



		float PitchToAdd = 0.f;
		float CurrentPitchOffset = 0.f;

		float YawToAdd = 0.f;
		float CurrentYawOffset = 0.f;
		
		bool bCurrentlymoving = false;
		AUnrealWeaponProjectCharacter* TargetCharacter = nullptr;
		UCameraComponent* Camera = nullptr;
	// Called every frame
	
	UFUNCTION(BlueprintCallable)
		void DoCameraShake(AUnrealWeaponProjectCharacter* Character);
		
private:

};
