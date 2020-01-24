// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "../UnrealWeaponProjectCharacter.h"
#include "WeaponComponentInterface.h"
#include "CameraShakeComponent.generated.h"
class UInputComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALWEAPONPROJECT_API UCameraShakeComponent : public UActorComponent, public IWeaponComponentInterface
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


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
			/** Time until the camera should start resetting after the player has stopped firring. 
			Timer resets to this value when the player starts firring.*/	
			float TimeUntillReset = 1.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			/**How much pitch to rotate the camera with when called.*/
			float PitchToAdd = 2.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			/**How much Yaw to rotate the camera with when called. */
			float YawToAdd = -2.f;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			/**If the camera should reset after the player stopped firring. 
			Time until the reset is represented by the "TimeUntillReset" variable.*/
			bool bRecoildReset = true;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			/**The speed that the camera adds the Pitch at.*/
			float PitchAddSpeed = -1.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			/**The speed that the camera adds the Yaw at.*/
			float YawAddSpeed = 1.f;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")	
			/**The speed that the camera resets the Pitch at.*/
			float PitchRemovedSpeed = 0.5f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			/**The speed that the camera resets the Yaw at.*/	
			float YawRemoveSpeed = 0.5f;


	
	UFUNCTION(BlueprintCallable)
		/** Main Camera Shake override function. Override need to be true for its values to apply. */
		void DoCameraShake(AActor* Character, bool bOverride = true,float O_PitchToAdd = 2.f, float O_YawToAdd = -2.f);

	void ActivateCameraShake();

	virtual void OnWeaponAttack_Implementation() override;
	virtual void OnWeaponEquipped_Implementation(AActor* NewHolder) override; 
	virtual void OnWeaponDropped_Implementation() override;
		
private:
	float timer = 0.f;

	float CurrentPitchOffset = 0.f;
	float CurrentYawOffset = 0.f;

	bool bPitchDone = false; // PitchDone and YawDone is used to see if both Pitch and Yaw are fully reset
	bool bYawDone = false; 

	float CurrentPitchToAdd = 0.f;
	float CurrentYawToAdd = 0.f;

	AActor* Holder = nullptr;
	AUnrealWeaponProjectCharacter* TargetCharacter = nullptr;
	

};
