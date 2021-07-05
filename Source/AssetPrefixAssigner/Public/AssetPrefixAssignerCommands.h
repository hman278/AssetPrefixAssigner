// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorStyleSet.h"
#include "AssetPrefixAssignerStyle.h"

class FAssetPrefixAssignerCommands : public TCommands<FAssetPrefixAssignerCommands>
{
public:

	FAssetPrefixAssignerCommands()
		: TCommands<FAssetPrefixAssignerCommands>(
			TEXT("AssetPrefixAssigner")
			, NSLOCTEXT("Contexts"
				, "AssetPrefixAssigner"
				, "AssetPrefixAssigner Plugin")
			, NAME_None, FAssetPrefixAssignerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginButton;
};
