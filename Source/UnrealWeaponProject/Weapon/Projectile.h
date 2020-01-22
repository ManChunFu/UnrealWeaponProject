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

	// Sphere component for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
		class USphereComponent* CollisionComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float GravityScale = 1.f;
	// Projectile Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ProjectileMesh;
protected:
	// Projectile Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;
	


	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// Called when the game starts or when spawned
	UFUNCTION()
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	UPROPERTY(EditAnywhere)
		float ProjectileSpeed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float Damage = 10.f;

private:
	void PrintDamagePerShotOnHUD(float Value, FString Multiplier);
};
