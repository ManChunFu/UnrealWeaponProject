// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeSpear.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Character.h"

void AMeleeSpear::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMeleeSpear::OnHit);
}

void AMeleeSpear::OnHit(AActor* ThisActor, AActor* OtherActor)
{
	if (OtherActor->IsA<ACharacter>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Attack"));

		UGameplayStatics::ApplyDamage(OtherActor, 10.f, Cast<ACharacter>(OtherActor)->GetController(), ThisActor, DamageClass);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
	}
}
