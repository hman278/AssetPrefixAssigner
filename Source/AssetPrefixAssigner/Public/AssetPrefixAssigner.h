// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FAssetPrefixAssignerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TSharedPtr<FExtender> ToolbarExtender;
	TSharedPtr<const FExtensionBase> Extension;
	
	/** This function will be bound to Command. */
	void AssetButtonClicked();

	void AddToolBarExtension(FToolBarBuilder& Builder);

private:

	//void RegisterMenus();


private:
	//TSharedPtr<class FUICommandList> PluginCommands;
};
