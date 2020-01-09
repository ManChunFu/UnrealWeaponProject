// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class UNREALWEAPONPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Projectile Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;
	// Projectile Mesh
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ProjectileMesh;

	// Called when the game starts or when spawned
	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnConstruction(const FTransform& Transform) override;

public:	

};
