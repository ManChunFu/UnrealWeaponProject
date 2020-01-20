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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
		float rate = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
		float speed = 1;
	
		float timer = 0;
		float test = 5;

	

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float MaxRandYaw = 1;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float MinRandYaw = 0;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float MaxRandPitch = 1;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
			float MinRandPitch = 0;

		float RandYaw = 0;
		float RandPitch = 0;

		float startYaw = 0;
		float startPitch = 0;

		float currentYaw = 0;
		float currentPitch = 0;

		float PitchToAdd = 0.f;
		float CurrentPitchOffset = 0.f;

		bool bCurrentlymoving = false;
		AUnrealWeaponProjectCharacter* TargetCharacter = nullptr;
		UCameraComponent* Camera = nullptr;
	// Called every frame
	
	UFUNCTION(BlueprintCallable)
		void DoCameraShake(AUnrealWeaponProjectCharacter* Character);
		
private:
	

};
