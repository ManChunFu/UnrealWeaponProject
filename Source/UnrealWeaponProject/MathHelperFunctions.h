// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MathHelperFunctions.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWEAPONPROJECT_API UMathHelperFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		static void GetRandomPointOnCircle(float& OutX, float& OutY);
};
