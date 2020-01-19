// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h" 
#include "WeaponComponentInterface.h"
#include "ScopeComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALWEAPONPROJECT_API UScopeComponent : public UActorComponent, public IWeaponComponentInterface
{
	GENERATED_BODY()

private:
	float OriginalFov = -1;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ZoomedFoV = 50.f;
	// Sets default values for this component's properties
	UScopeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Zoom(UCameraComponent* Camera);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
