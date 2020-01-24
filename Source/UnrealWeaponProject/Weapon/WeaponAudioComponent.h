// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponentInterface.h"
#include "WeaponAudioComponent.generated.h"

class UAudioComponent;

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class UNREALWEAPONPROJECT_API UWeaponAudioComponent : public UActorComponent, public IWeaponComponentInterface
{
	GENERATED_BODY()

public:	
	/*
	* Sets default values for this component's properties
	*/
	UWeaponAudioComponent();

protected:
	/*
	* Called when the game starts
	*/
	virtual void BeginPlay() override;

public:	
	/*
	* Called every frame
	*/
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	* This firing weapon sound plays when weapon fires
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class USoundBase* FireSoundCue = nullptr;

	/*
	* This reloading magazine sound plays when realod the magazine
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		class USoundBase* ReloadSoundCue = nullptr;

	/*
	* This weapon equipped sound plays when the player picks up a weapon
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		class USoundBase* WeaponEquippedSoundCue = nullptr;

	/*
	* This weapon dropped sound plays when the player throw away a gun
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		class USoundBase* WeaponDroppedSoundCue = nullptr;


	virtual void OnWeaponEquipped_Implementation(AActor* NewHolder) override;

	virtual void OnWeaponDropped_Implementation() override;

	virtual void OnWeaponAttack_Implementation() override;

	virtual void OnWeaponReload_Implementation() override;

	/*
	* This function allows you to play sound, it requires a SoundCue, Starting time, and Volume
	*/
	UFUNCTION()
		void PlaySoundCue(USoundBase* SoundCue, float StartTime, int32 VolumeMultiplier);

	/*
	* This function allows you to stop playing sound if it is playing
	*/
	UFUNCTION()
		void StopSoundCue();


private:
	UAudioComponent* AudioComponent;
	bool bHasPlayed = false;
		
};
