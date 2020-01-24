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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FireAnimationMontageObject(TEXT("AnimMontage'/Game/FirstPerson/Animations/FirstPersonFire_Montage.FirstPersonFire_Montage'")); // Get the file referernce
	if (FireAnimationMontageObject.Succeeded())
	{
		FireAnimationMontage = FireAnimationMontageObject.Object; // Assign the file as default
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ReloadAnimationMontageObject(TEXT("AnimMontage'/Game/FirstPerson/Character/Mesh/Reload_mixamo_com_Montage.Reload_mixamo_com_Montage'"));
	if (ReloadAnimationMontageObject.Succeeded())
	{
		ReloadAnimationMontage = ReloadAnimationMontageObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemObject(TEXT("ParticleSystem'/Game/Effects/Weapons/Muzzle/P_AssaultRifle_MF.P_AssaultRifle_MF'"));
	if (ParticleSystemObject.Succeeded())
	{
		MuzzleFlash = ParticleSystemObject.Object;
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
	if (MuzzleFlash == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("--------------------NoParticle-----------------------"));
	}
}


void UWeaponAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UWeaponAnimationComponent::OnWeaponAttack_Implementation()
{
	if (Player && FireAnimationMontage)
	{
		UAnimInstance* AnimInstance = Player->Mesh1P->GetAnimInstance(); // Get handle of player's AnimInstance
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(FireAnimationMontage, 1.f);
		}
	}

	if (Weapon && MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), MuzzleFlash, Weapon->WeaponMesh->GetSocketLocation("Muzzle"), Weapon->WeaponMesh->GetSocketRotation("Muzzle"), 
			true, EPSCPoolMethod::None, true); // spawn particle system from gun's muzzle socket
	}
}

void UWeaponAnimationComponent::OnWeaponReload_Implementation()
{
	if (Player && ReloadAnimationMontage)
	{
		UAnimInstance* AnimInstance = Player->Mesh1P->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(ReloadAnimationMontage, 1.f);
		}
	}
}

