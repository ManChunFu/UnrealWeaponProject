// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "StaticMeshResources.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AProjectile::OnConstruction(const FTransform& Transform)
{


	Super::OnConstruction(Transform);
	this->SetActorTickEnabled(true);
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 30000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	// Die after 30 seconds by default
	InitialLifeSpan = 30.0f;
	UE_LOG(LogTemp, Warning, TEXT("Spawned Projectile"));
}


