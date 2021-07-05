// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AssetPrefixAssigner/Public/AssetProperties.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAssetProperties() {}
// Cross Module References
	ASSETPREFIXASSIGNER_API UScriptStruct* Z_Construct_UScriptStruct_FAssetProperties();
	UPackage* Z_Construct_UPackage__Script_AssetPrefixAssigner();
// End Cross Module References
class UScriptStruct* FAssetProperties::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ASSETPREFIXASSIGNER_API uint32 Get_Z_Construct_UScriptStruct_FAssetProperties_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAssetProperties, Z_Construct_UPackage__Script_AssetPrefixAssigner(), TEXT("AssetProperties"), sizeof(FAssetProperties), Get_Z_Construct_UScriptStruct_FAssetProperties_Hash());
	}
	return Singleton;
}
template<> ASSETPREFIXASSIGNER_API UScriptStruct* StaticStruct<FAssetProperties>()
{
	return FAssetProperties::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAssetProperties(FAssetProperties::StaticStruct, TEXT("/Script/AssetPrefixAssigner"), TEXT("AssetProperties"), false, nullptr, nullptr);
static struct FScriptStruct_AssetPrefixAssigner_StaticRegisterNativesFAssetProperties
{
	FScriptStruct_AssetPrefixAssigner_StaticRegisterNativesFAssetProperties()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AssetProperties")),new UScriptStruct::TCppStructOps<FAssetProperties>);
	}
} ScriptStruct_AssetPrefixAssigner_StaticRegisterNativesFAssetProperties;
	struct Z_Construct_UScriptStruct_FAssetProperties_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Class_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_Class;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Prefix_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_Prefix;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAssetProperties_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AssetProperties.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAssetProperties_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAssetProperties>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Class_MetaData[] = {
		{ "ModuleRelativePath", "Public/AssetProperties.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Class = { "Class", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAssetProperties, Class), METADATA_PARAMS(Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Class_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Class_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Prefix_MetaData[] = {
		{ "ModuleRelativePath", "Public/AssetProperties.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Prefix = { "Prefix", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAssetProperties, Prefix), METADATA_PARAMS(Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Prefix_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Prefix_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAssetProperties_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Class,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAssetProperties_Statics::NewProp_Prefix,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAssetProperties_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AssetPrefixAssigner,
		nullptr,
		&NewStructOps,
		"AssetProperties",
		sizeof(FAssetProperties),
		alignof(FAssetProperties),
		Z_Construct_UScriptStruct_FAssetProperties_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetProperties_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAssetProperties_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAssetProperties_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAssetProperties()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAssetProperties_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_AssetPrefixAssigner();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AssetProperties"), sizeof(FAssetProperties), Get_Z_Construct_UScriptStruct_FAssetProperties_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UECodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAssetProperties_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAssetProperties_Hash() { return 1068525365U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
