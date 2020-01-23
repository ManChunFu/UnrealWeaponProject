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
	// Sets default values for this component's properties
	UWeaponAudioComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class USoundBase* FireSoundCue = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		class USoundBase* ReloadSoundCue = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		class USoundBase* WeaponEquippedSoundCue = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		class USoundBase* WeaponDroppedSoundCue = nullptr;


	virtual void OnWeaponEquipped_Implementation(AActor* NewHolder) override;

	virtual void OnWeaponDropped_Implementation() override;

	virtual void OnWeaponAttack_Implementation() override;

	virtual void OnWeaponReload_Implementation() override;


	UFUNCTION()
		void PlaySound(USoundBase* SoundCue, float StartTime);

	UFUNCTION()
		void StopSound();


private:
	UAudioComponent* AudioComponent;
	bool bHasPlayed = false;
		
};
