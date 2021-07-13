//  © 2021 hman278

#include "AssetPrefixAssigner.h"
#include "AssetPrefixAssignerStyle.h"
#include "AssetPrefixAssignerCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

#include "LevelEditor.h"
#include "SlateBasics.h"
#include "Framework/MultiBox/MultiBoxExtender.h"
#include "Engine/ObjectLibrary.h"
#include "Misc/FileHelper.h" 
#include "Serialization/JsonReader.h" 
#include "Templates/SharedPointer.h" 
#include "JsonObjectConverter.h" 
#include "AssetProperties.h"
#include "AssetToolsModule.h"

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
}

void FAssetPrefixAssignerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAssetPrefixAssignerStyle::Shutdown();

	FAssetPrefixAssignerCommands::Unregister();
}

void FAssetPrefixAssignerModule::PluginButtonClicked()
{           
	const FString Path = FPaths::ProjectUserDir().Append(
		TEXT("Plugins/AssetPrefixAssigner/Resources/AssetProperties.json"));
	const FString PathBp = FPaths::ProjectUserDir().Append(
		TEXT("Plugins/AssetPrefixAssigner/Resources/BlueprintAssetProperties.json"));

	/* Make sure the json files are valid
	otherwise present a dialog box with an error message */
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*Path))
	{
		FText DialogText = FText::Format(
			LOCTEXT("PluginButtonDialogText", "File doesn't exist, {0}")
			, FText::FromString(*Path));
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		return;
	}
	else if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*PathBp))
	{
		FText DialogText = FText::Format(
			LOCTEXT("PluginButtonDialogText", "File doesn't exist, {0}")
			, FText::FromString(*PathBp));
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		return;
	}

	FString JsonContent;
	FString JsonContentBp;

	/* Initialize json file contents into strings */
	FFileHelper::LoadFileToString(JsonContent, *Path);
	FFileHelper::LoadFileToString(JsonContentBp, *PathBp);

	TArray<FAssetProperties> Properties;
	TArray<FAssetProperties> PropertiesBp;

	/* Initialize json file contents into TArray-s of FAssetProperties */
	if (!FJsonObjectConverter::JsonArrayStringToUStruct(JsonContent, &Properties, 0, 0))
	{
		FText DialogText = FText::Format(
			LOCTEXT("PluginButtonDialogText", "Couldn't deserialize json string into the Properties array, {0}"), FText::FromString(""));
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		return;
	}
	else if (!FJsonObjectConverter::JsonArrayStringToUStruct(JsonContentBp, &PropertiesBp, 0, 0))
	{
		FText DialogText = FText::Format(
			LOCTEXT("PluginButtonDialogText", "Couldn't deserialize json string into the PropertiesBp array, {0}"), FText::FromString(""));
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		return;
	}

	/* Load game assets */
	UObjectLibrary* AssetLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), true, true);
	AssetLibrary->AddToRoot();

	AssetLibrary->LoadAssetDataFromPath(TEXT("/Game"));

	TArray<FAssetData> AssetDatas;
	AssetLibrary->GetAssetDataList(AssetDatas);

	FAssetToolsModule& AssetToolsModule = 
		FModuleManager::LoadModuleChecked< FAssetToolsModule>("AssetTools");

#define LOCTEXT_NAMESPACE "Asset Namespace"

	/* Create a progress bar for the editor */
	FScopedSlowTask AssetRenameTask(AssetDatas.Num(), LOCTEXT("Asset Rename", "Renaming Assets..."));
	AssetRenameTask.MakeDialog(true);

	/* Rename the assets */
	for (FAssetData& Asset : AssetDatas)
	{
		if (AssetRenameTask.ShouldCancel())
		{
			break;
		}

		UE_LOG(LogTemp, Log, TEXT("Asset %s of type %s"), *Asset.AssetName.ToString(), *Asset.AssetClass.ToString());

		if (Asset.GetClass() == UBlueprint::StaticClass())
		{
			UClass* AssetBp = StaticLoadClass(
				UObject::StaticClass(), nullptr
				, *FString::Printf(TEXT("Blueprint'%s_C'")
				, *Asset.ObjectPath.ToString()));

			if (AssetBp != nullptr)
			{
				FString Archetype = AssetBp->GetArchetypeForCDO()->GetFName().ToString();

				for (FAssetProperties& Prop : PropertiesBp)
				{
					if ( Archetype.EndsWith(Prop.Class.ToString()
						, ESearchCase::Type::CaseSensitive)
						&&
						 !Asset.AssetName.ToString().StartsWith(
						 Prop.Prefix.ToString(), ESearchCase::Type::CaseSensitive))
					{
						UE_LOG(
							LogTemp, Log, TEXT("Asset %s is of type %s without the prefix %s"),
							*Archetype, *Prop.Class.ToString(), *Prop.Prefix.ToString());

						TArray<FAssetRenameData> Ren;
						
						Ren.Add(*new FAssetRenameData(
							Asset.GetAsset()
							, Asset.PackagePath.ToString()
							, Prop.Prefix.ToString() + Asset.AssetName.ToString()));

						AssetToolsModule.Get().RenameAssets(Ren);
					}
				}
			}
		}
		else 
		{
			for (FAssetProperties& Prop : Properties)
			{	
				if ((Asset.AssetClass == Prop.Class)
					&&
					(!Asset.AssetName.ToString().StartsWith(
						Prop.Prefix.ToString(), ESearchCase::Type::CaseSensitive)))
				{
					TArray<FAssetRenameData> Ren;
					
					Ren.Add(*new FAssetRenameData(
						Asset.GetAsset()
						, Asset.PackagePath.ToString()
						, Prop.Prefix.ToString() + Asset.AssetName.ToString()));

					AssetToolsModule.Get().RenameAssets(Ren);
				}
			}
		}
		AssetRenameTask.EnterProgressFrame(1);
	}

	FText DialogText = FText::Format(
		LOCTEXT("PluginButtonDialogText", "{0}"), FText::FromString("Assets have been successfully renamed"));
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}
#undef LOCTEXT_NAMESPACE

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