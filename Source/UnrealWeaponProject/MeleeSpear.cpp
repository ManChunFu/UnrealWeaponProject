// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeSpear.h"

void AMeleeSpear::OnConstruction(const FTransform& Transform)
{
	ArmsMesh->AttachToComponent(WeaponRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ArmsMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	ArmsMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	//WeaponMesh->AttachToComponent(ArmsMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, "GripPoint");
}

void AMeleeSpear::Attack()
{

}
