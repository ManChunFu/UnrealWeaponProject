// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponHitScan.h"
#include "Math/RandomStream.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
void AWeaponHitScan::Attack()
{

	
	FHitResult* HitResult = new FHitResult();

	//FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	FVector StartTrace = GetActorLocation();
	
	//FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector ForwardVector = GetActorLocation();


	float test1 = FMath::RandRange(-0.05f, 0.05f);
	float test2 = FMath::RandRange(-0.05f, 0.05f);
	FVector TestVector = ForwardVector;

	TestVector.Y -= test1;
	TestVector.Z -= test2;

	FVector EndTrace = ((TestVector * 2000.f) + StartTrace);

	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 5.f);

		/*ATarget* TestTarget = Cast<ATarget>(HitResult->Actor.Get());

		if (TestTarget != NULL && !TestTarget->IsPendingKill())
		{
			TestTarget->DamageTarget(50.f);
		}*/


	}

}