// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAudioComponent.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UWeaponAudioComponent::UWeaponAudioComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}


// Called when the game starts
void UWeaponAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponAudioComponent::PlaySound(USoundBase* SoundCue, float StartTime)
{
	if (AudioComponent && SoundCue)
	{
		AudioComponent->SetSound(SoundCue);
		AudioComponent->Play(0.0f);
	}
}

void UWeaponAudioComponent::StopSound()
{
	if (AudioComponent && AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}

}



