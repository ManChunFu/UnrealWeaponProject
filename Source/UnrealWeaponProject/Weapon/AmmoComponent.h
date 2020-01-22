// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "WeaponComponentInterface.h"
#include "AmmoComponent.generated.h"

class UAudioComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALWEAPONPROJECT_API UAmmoComponent : public UActorComponent, public IWeaponComponentInterface
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		float ReloadTime = 2.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		int32 MagazineSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 SpareAmmo = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 MagazineAmmo = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		int32 MaxSpareAmmo = 200;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		bool Reload();
	

	// only empty magazine sound calling from this class.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Audio")
		class USoundBase* EmptyMagazineSoundCue = nullptr;

	bool CanAttack_Implementation();

	virtual void OnWeaponAttack_Implementation() override;

private:
	FTimerHandle ReloadTimer;
	//The weapon this component is attached to
	class AWeapon* Weapon = nullptr;
	UFUNCTION()
		void FinishReload();

	UAudioComponent* SoundAudioComponent;
	void PlaySound(USoundBase* SoundCue);

};
