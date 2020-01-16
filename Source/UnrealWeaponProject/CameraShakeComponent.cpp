// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShakeComponent.h"

// Sets default values for this component's properties
UCameraShakeComponent::UCameraShakeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraShakeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCameraShakeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCameraShakeComponent::DoCameraShake(UCameraComponent* Camera)
{
	FRotator NewRotation = FRotator(1.f, 1.f, 1.f);
	FQuat QuatRotation = FQuat(NewRotation);
	Camera->AddWorldRotation(QuatRotation, false, 0, ETeleportType::None);
	
}

