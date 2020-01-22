// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAnimationComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/PlayerController.h"	
#include "GameFramework/PlayerController.h"	
#include "Animation/AnimInstance.h"


// Sets default values for this component's properties
UWeaponAnimationComponent::UWeaponAnimationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FireAnimationMontageObject(TEXT("AnimMontage'/Game/FirstPerson/Animations/FirstPersonFire_Montage.FirstPersonFire_Montage'"));
	if (FireAnimationMontageObject.Succeeded())
	{
		FireAnimationMontage = FireAnimationMontageObject.Object;
	}
}


// Called when the game starts
void UWeaponAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponAnimationComponent::OnWeaponReload_Implementation()
{
	/*UWorld* world = GetWorld();
	if (world != nullptr)
	{
		auto Player = Cast<ACharacter>(world->GetFirstPlayerController()->GetCharacter());
		if (Player != nullptr)
			Player->PlayAnimMontage(FireAnimationMontage, 1.f, FName("Default"));
	}
	if (FireAnimationMontage)
	{
		if (Player)
			Player->PlayAnimMontage(FireAnimationMontage, 1.f, FName("Default"));
	}

	if (FireAnimationMontage)
	{
		UAnimInstance* AnimInstance = Player->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(FireAnimationMontage, 1.f);
		}
	}*/
}

