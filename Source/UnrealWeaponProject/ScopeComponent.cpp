// Fill out your copyright notice in the Description page of Project Settings.

#include "ScopeComponent.h"
#include "Weapon.h"

// Sets default values for this component's properties
UScopeComponent::UScopeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScopeComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void UScopeComponent::Zoom(UCameraComponent* Camera)
{
	if (OriginalFov == -1)
	{
		OriginalFov = Camera->FieldOfView;
	}

	if (Camera->FieldOfView == OriginalFov)
	{
		Camera->FieldOfView = ZoomedFoV;
	}
	else
	{
		Camera->FieldOfView = OriginalFov;
	}
}


// Called every frame
void UScopeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

