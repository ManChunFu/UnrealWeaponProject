// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "AmmoComponent.generated.h"

class UAudioComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALWEAPONPROJECT_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAmmoComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
		bool bIsReloading = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float ReloadTime = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 MagazineSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 SpareAmmo = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 MagazineAmmo = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 MaxSpareAmmo = 200;


	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Reload();


	UFUNCTION(BlueprintCallable, Category = "Weapon")
		bool DecreaseAmmo(int32 Amount = 1);


	// Audio sound setting for reloading and empty magazine
	// TODO try to move to weapon class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Audio")
		class USoundBase* ReloadSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Audio")
		class USoundBase* EmptyMagazineSoundCue;

private:
	FTimerHandle ReloadTimer;
	//The weapon this component is attached to
	class AWeapon* Weapon = nullptr;
	UFUNCTION()
		void FinishReload();

	UAudioComponent* SoundAudioComponent;
	void PlaySound(USoundBase* SoundCue);
};
