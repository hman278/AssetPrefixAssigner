//  © 2021 hman278

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

	void PluginButtonClicked();

private:

	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
