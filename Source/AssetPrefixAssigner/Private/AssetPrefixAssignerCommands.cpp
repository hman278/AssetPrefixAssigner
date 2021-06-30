// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetPrefixAssignerCommands.h"

#define LOCTEXT_NAMESPACE "FAssetPrefixAssignerModule"

void FAssetPrefixAssignerCommands::RegisterCommands()
{
	UI_COMMAND(PluginButton
		, "AssetPrefixAssigner"
		, "Execute AssetPrefixAssigner action"
		, EUserInterfaceActionType::Button
		, FInputGesture());

	UI_COMMAND(AssetButton
		, "AssetPrefixAssigner"
		, "Execute AssetPrefixAssigner action"
		, EUserInterfaceActionType::Button
		, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
