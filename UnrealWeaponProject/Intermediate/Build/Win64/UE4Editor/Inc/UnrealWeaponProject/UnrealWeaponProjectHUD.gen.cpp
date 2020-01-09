// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealWeaponProject/UnrealWeaponProjectHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealWeaponProjectHUD() {}
// Cross Module References
	UNREALWEAPONPROJECT_API UClass* Z_Construct_UClass_AUnrealWeaponProjectHUD_NoRegister();
	UNREALWEAPONPROJECT_API UClass* Z_Construct_UClass_AUnrealWeaponProjectHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_UnrealWeaponProject();
// End Cross Module References
	void AUnrealWeaponProjectHUD::StaticRegisterNativesAUnrealWeaponProjectHUD()
	{
	}
	UClass* Z_Construct_UClass_AUnrealWeaponProjectHUD_NoRegister()
	{
		return AUnrealWeaponProjectHUD::StaticClass();
	}
	struct Z_Construct_UClass_AUnrealWeaponProjectHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUnrealWeaponProjectHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealWeaponProject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUnrealWeaponProjectHUD_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "UnrealWeaponProjectHUD.h" },
		{ "ModuleRelativePath", "UnrealWeaponProjectHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUnrealWeaponProjectHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUnrealWeaponProjectHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AUnrealWeaponProjectHUD_Statics::ClassParams = {
		&AUnrealWeaponProjectHUD::StaticClass,
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
		0x008002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AUnrealWeaponProjectHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUnrealWeaponProjectHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUnrealWeaponProjectHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AUnrealWeaponProjectHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AUnrealWeaponProjectHUD, 499852288);
	template<> UNREALWEAPONPROJECT_API UClass* StaticClass<AUnrealWeaponProjectHUD>()
	{
		return AUnrealWeaponProjectHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AUnrealWeaponProjectHUD(Z_Construct_UClass_AUnrealWeaponProjectHUD, &AUnrealWeaponProjectHUD::StaticClass, TEXT("/Script/UnrealWeaponProject"), TEXT("AUnrealWeaponProjectHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealWeaponProjectHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
