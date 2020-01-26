// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h" 
#include "WeaponComponentInterface.h"
#include "ScopeComponent.generated.h"

class UAudioComponent;

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class UNREALWEAPONPROJECT_API UScopeComponent : public UActorComponent, public IWeaponComponentInterface
{
	GENERATED_BODY()

private:
	float OriginalFov = -1;
	UCameraComponent* HolderCamera = nullptr;
public:
	UScopeComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float ZoomedFoV = 50.f;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Weapon")
	bool bIsZoomedIn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Audio")
	class USoundBase* ZoomSoundCue = nullptr;
protected:
	virtual void BeginPlay() override;

	/** Toggles zoom */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Zoom();

public:
	virtual void OnWeaponEquipped_Implementation(AActor* NewHolder) override;
	virtual void OnWeaponDropped_Implementation() override;

	UAudioComponent* AudioComponent;
	void PlaySoundCue(USoundBase* SoundCue, float StartTime, float VolumMultiplier);
};
