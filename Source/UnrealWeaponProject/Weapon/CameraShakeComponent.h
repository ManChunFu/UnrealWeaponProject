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
		float TimeUntillReset = 1.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float PitchToAdd = 2.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float YawToAdd = -2.f;
		
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


	
	UFUNCTION(BlueprintCallable)
		void DoCameraShake(AActor* Character, bool bOverride = false,float O_PitchToAdd = 2.f, float O_YawToAdd = -2.f);

	void ActivateCameraShake();
	virtual void OnWeaponAttack_Implementation() override;
	virtual void OnWeaponEquipped_Implementation(AActor* NewHolder) override; 
	virtual void OnWeaponDropped_Implementation() override;
		
private:
	float timer = 0.f;

	float CurrentPitchOffset = 0.f;
	float CurrentYawOffset = 0.f;
	bool bPitchDone = false;
	bool bYawDone = false;

	float CurrentPitchToAdd = 0.f;
	float CurrentYawToAdd = 0.f;
	AActor* Holder = nullptr;
	AUnrealWeaponProjectCharacter* TargetCharacter = nullptr;
	UCameraComponent* Camera = nullptr;

};
