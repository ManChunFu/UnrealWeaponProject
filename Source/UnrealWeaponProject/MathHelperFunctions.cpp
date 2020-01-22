// Fill out your copyright notice in the Description page of Project Settings.


#include "MathHelperFunctions.h"

void UMathHelperFunctions::GetRandomPointOnCircle(float& OutX, float& OutY)
{
	// Formula from https://programming.guide/random-point-within-circle.html

	float a = FMath::RandRange(0.f, 1.f) * 2.f * PI;
	float r = sqrt(FMath::RandRange(0.f, 1.f));
	OutX = r* cosf(a);
	OutY = r* sinf(a);
}
