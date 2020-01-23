// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAnimationComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "UnrealWeaponProject/UnrealWeaponProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Particles/ParticleSystemComponent.h"
#include "Weapon.h"


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

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemObject(TEXT("ParticleSystem'/Game/Effects/Weapons/Muzzle/P_AssaultRifle_MF.P_AssaultRifle_MF'"));
	if (ParticleSystemObject.Succeeded())
	{
		ParticleSystem = ParticleSystemObject.Object;
	}
		

}


// Called when the game starts
void UWeaponAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		Player = Cast<AUnrealWeaponProjectCharacter>(World->GetFirstPlayerController()->GetCharacter());
	}

	Weapon = Cast<AWeapon>(GetOwner());
	if (ParticleSystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("--------------------NoParticle-----------------------"));
	}
}


// Called every frame
void UWeaponAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponAnimationComponent::OnWeaponEquipped_Implementation(AActor* NewHolder)
{
	Holder = NewHolder;
	Holder = Cast<AUnrealWeaponProjectCharacter>(Holder);
}

void UWeaponAnimationComponent::OnWeaponAttack_Implementation()
{
	if (Player && FireAnimationMontage)
	{
		UAnimInstance* AnimInstance = Player->Mesh1P->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(FireAnimationMontage, 1.f);
		}
	}

	if (Weapon && ParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, Weapon->WeaponMesh->GetSocketLocation("Muzzle"), Weapon->WeaponMesh->GetSocketRotation("Muzzle"));
		UE_LOG(LogTemp, Warning, TEXT("--------------------Spawning-----------------------"));
		
	}
}

void UWeaponAnimationComponent::OnWeaponReload_Implementation()
{
	if (Player && FireAnimationMontage)
	{
		UAnimInstance* AnimInstance = Player->Mesh1P->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(FireAnimationMontage, 1.f);
		}
	}
}

