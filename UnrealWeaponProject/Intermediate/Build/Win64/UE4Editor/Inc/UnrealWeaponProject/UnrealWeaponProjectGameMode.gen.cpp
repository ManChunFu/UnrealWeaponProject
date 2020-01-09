// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealWeaponProject/UnrealWeaponProjectGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealWeaponProjectGameMode() {}
// Cross Module References
	UNREALWEAPONPROJECT_API UClass* Z_Construct_UClass_AUnrealWeaponProjectGameMode_NoRegister();
	UNREALWEAPONPROJECT_API UClass* Z_Construct_UClass_AUnrealWeaponProjectGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_UnrealWeaponProject();
// End Cross Module References
	void AUnrealWeaponProjectGameMode::StaticRegisterNativesAUnrealWeaponProjectGameMode()
	{
	}
	UClass* Z_Construct_UClass_AUnrealWeaponProjectGameMode_NoRegister()
	{
		return AUnrealWeaponProjectGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AUnrealWeaponProjectGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUnrealWeaponProjectGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealWeaponProject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUnrealWeaponProjectGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "UnrealWeaponProjectGameMode.h" },
		{ "ModuleRelativePath", "UnrealWeaponProjectGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUnrealWeaponProjectGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUnrealWeaponProjectGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AUnrealWeaponProjectGameMode_Statics::ClassParams = {
		&AUnrealWeaponProjectGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AUnrealWeaponProjectGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUnrealWeaponProjectGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUnrealWeaponProjectGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AUnrealWeaponProjectGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AUnrealWeaponProjectGameMode, 2948889659);
	template<> UNREALWEAPONPROJECT_API UClass* StaticClass<AUnrealWeaponProjectGameMode>()
	{
		return AUnrealWeaponProjectGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AUnrealWeaponProjectGameMode(Z_Construct_UClass_AUnrealWeaponProjectGameMode, &AUnrealWeaponProjectGameMode::StaticClass, TEXT("/Script/UnrealWeaponProject"), TEXT("AUnrealWeaponProjectGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealWeaponProjectGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
