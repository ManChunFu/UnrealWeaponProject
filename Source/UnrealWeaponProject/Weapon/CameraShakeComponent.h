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

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CamShake")
			/**Time until the camera starts reseting after the gun has stopped firring.*/	
			float TimeUntillReset = 1.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CamShake")
			/**If the camera should reset itself after being fired, Time until reset is represented by "TimeUntillReset" */
			bool bRecoildReset = true;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CamShake |Add Value")
			/**How Much Pitch to add whenever the gun fires*/
			float PitchToAdd = 2.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CamShake |Add Value")
			/**How Much Yaw to add whenever the gun fires*/
			float YawToAdd = -2.f;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CamShake |Speed")
			/**How fast the camera should move when adding Pitch*/
			float PitchAddSpeed = -1.f;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CamShake |Speed")
			/**How fast the camera should move when adding Yaw*/
			float YawAddSpeed = 1.f;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CamShake |RemoveRate")	
			/**How fast the camera should move when resetting Pitch*/
			float PitchRemovedRate = 0.5f;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CamShake |RemoveRate")
			/**How fast the camera should move when resetting Yaw*/
			float YawRemoveRate = 0.5f;


	
	UFUNCTION(BlueprintCallable)
		/**Node to override the standard input values.*/
		void DoCameraShake(float O_PitchToAdd = 2.f, float O_YawToAdd = -2.f);

	void ActivateCameraShake();
	virtual void OnWeaponAttack_Implementation() override;
	virtual void OnWeaponEquipped_Implementation(AActor* NewHolder) override; 
	virtual void OnWeaponDropped_Implementation() override;
		
private:
	float timer = 0.f;

	float CurrentPitchOffset = 0.f;
	float CurrentYawOffset = 0.f;
	bool bPitchDone = false; // bPitchDone and bYawDone checks if the pitch and yaw have been reset.
	bool bYawDone = false;

	float CurrentPitchToAdd = 0.f;
	float CurrentYawToAdd = 0.f;
	AActor* Holder = nullptr;
	AUnrealWeaponProjectCharacter* TargetCharacter = nullptr;
	

};
