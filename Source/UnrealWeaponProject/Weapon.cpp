// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "UnrealWeaponProjectCharacter.h"
#include "WeaponComponentInterface.h"
#include "Camera/CameraComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetCollisionProfileName("Weapon");
	BarrelEnd = CreateDefaultSubobject<UArrowComponent>(TEXT("Barrel End"));
	BarrelEnd->SetupAttachment(WeaponMesh);
	RootComponent = WeaponMesh;
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	BarrelEnd->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

void AWeapon::Drop()
{
	// Notify components they weapon was dropped
	//TArray<UActorComponent*> Components = this->GetInstanceComponents();
	//for (UActorComponent* Component : Components)
	//{
	//	if (Component->Implements<IWeaponComponentInterface>())
	//	{
	//		Cast<IWeaponComponentInterface>(Component)->OnWeaponDropped();
	//	}
	//}

	WeaponMesh->SetGenerateOverlapEvents(false);
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->AddImpulse(WeaponMesh->GetRightVector() * 5000.f + Holder->GetRootComponent()->GetUpVector() * 2000.f);
	StopAttack();
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Holder = nullptr;

	// Wait two seconds before letting the weapon be overlappable again
	if (!DropDelegate.IsBound())
	{
		DropDelegate.BindLambda([=]
			{
				WeaponMesh->SetGenerateOverlapEvents(true);
			});
	}
	GetWorld()->GetTimerManager().SetTimer(DropHandle, DropDelegate, 2.f, false);
}

void AWeapon::Equip(AActor* NewHolder, USceneComponent* AttachTo, FName SocketName)
{
	Holder = NewHolder;
	if (Holder->IsA<AUnrealWeaponProjectCharacter>())
	{
		SpawnPoint = &Cast<AUnrealWeaponProjectCharacter>(Holder)->GetFirstPersonCameraComponent()->GetComponentTransform();

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Start Attack"));

		SpawnPoint = &BarrelEnd->GetComponentTransform();
	}
	WeaponMesh->SetSimulatePhysics(false);
	WeaponMesh->AttachToComponent(AttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);


	// Notify components they weapon was picked up
	//TArray<UActorComponent*> Components = this->GetInstanceComponents();
	//for (UActorComponent* Component : Components)
	//{
	//	if (Component->Implements<IWeaponComponentInterface>())
	//	{
	//		Cast<IWeaponComponentInterface>(Component)->OnWeaponEquipped();
	//	}
	//}

}


