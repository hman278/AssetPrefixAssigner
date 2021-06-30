// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetPrefixAssigner.h"
#include "AssetPrefixAssignerStyle.h"
#include "AssetPrefixAssignerCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Textures/SlateIcon.h"
#include "SlateExtras.h"
#include "SlateBasics.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxExtender.h"
#include "Engine/ObjectLibrary.h"

static const FName AssetPrefixAssignerTabName("AssetPrefixAssigner");

#define LOCTEXT_NAMESPACE "FAssetPrefixAssignerModule"

void FAssetPrefixAssignerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAssetPrefixAssignerStyle::Initialize();
	FAssetPrefixAssignerStyle::ReloadTextures();

	FAssetPrefixAssignerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAssetPrefixAssignerCommands::Get().PluginButton,
		FExecuteAction::CreateRaw(this, &FAssetPrefixAssignerModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAssetPrefixAssignerModule::RegisterMenus));

	TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList());

	CommandList->MapAction(
		FAssetPrefixAssignerCommands::Get().AssetButton,
		FExecuteAction::CreateRaw(this, &FAssetPrefixAssignerModule::PluginButtonClicked),
		FCanExecuteAction());

	ToolbarExtender = MakeShareable(new FExtender());
	Extension = ToolbarExtender->AddToolBarExtension("EditorModes", EExtensionHook::After,
		CommandList, FToolBarExtensionDelegate::CreateRaw(
		this, &FAssetPrefixAssignerModule::AddToolBarExtension));

	FLevelEditorModule& LevelEditorModule = 
		FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FAssetPrefixAssignerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	Extension.Reset();
	ToolbarExtender.Reset();

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAssetPrefixAssignerStyle::Shutdown();

	FAssetPrefixAssignerCommands::Unregister();
}

void FAssetPrefixAssignerModule::PluginButtonClicked()
{
	UObjectLibrary* AssetLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), true, true);
	AssetLibrary->AddToRoot();

	AssetLibrary->LoadAssetDataFromPath(TEXT("/Game"));

	TArray<FAssetData> AssetDatas;
	AssetLibrary->GetAssetDataList(AssetDatas);

	for (FAssetData& Asset : AssetDatas)
	{
		if (Asset.GetClass()->IsChildOf(UBlueprintCore::StaticClass()))
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *Asset.AssetName.ToString());
		}
	}

	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
		LOCTEXT("PluginButtonDialogText", "{0}"), FText::FromString("Assets have been successfully renamed"));
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FAssetPrefixAssignerModule::AddToolBarExtension(FToolBarBuilder& Builder)
{
	/*FSlateIcon IconBrush = FSlateIcon(FEditorStyle::GetStyleSetName()
		, "LevelEditor.ViewOptions"
		, "LevelEditor.ViewOptions.Small");*/

	Builder.AddToolBarButton(FAssetPrefixAssignerCommands::Get().PluginButton
		, NAME_None
		, FText::FromString("Rename Assets")
		, FText::FromString("Rename Assets"));
}

void FAssetPrefixAssignerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAssetPrefixAssignerCommands::Get().PluginButton, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAssetPrefixAssignerCommands::Get().PluginButton));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetPrefixAssignerModule, AssetPrefixAssigner)