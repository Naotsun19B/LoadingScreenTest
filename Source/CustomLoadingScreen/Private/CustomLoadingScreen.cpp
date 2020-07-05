// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomLoadingScreen.h"
#include "CustomLoadingScreenSettings.h"
#include "SCustomLoadingScreen.h"
#include "Framework/Application/SlateApplication.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#endif

#define LOCTEXT_NAMESPACE "CustomLoadingScreen"

class FCustomLoadingScreenModule : public ICustomLoadingScreenModule
{
public:
	FCustomLoadingScreenModule();

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool IsGameModule() const override { return true; }

	virtual void StartLoadingScreen(bool bOverrideSettings, FOverrideAttributes Settings) override;
	virtual void StopLoadingScreen() override;

private:
	//void HandlePrepareCustomLoadingScreen();

	void ShowLoadingScreen(const FCustomLoadingScreenDescription& ScreenDescription);
};

IMPLEMENT_MODULE(FCustomLoadingScreenModule, CustomLoadingScreen)

FCustomLoadingScreenModule::FCustomLoadingScreenModule()
{

}

void FCustomLoadingScreenModule::StartupModule()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"LodingScreen",
			"LodingScreenSetting",
			LOCTEXT("SettingName", "LodingScreenSetting"),
			LOCTEXT("SettingDescription", "Settings for the loading screen."),
			GetMutableDefault<UCustomLoadingScreenSettings>()
		);
	}
#endif

	if ( !IsRunningDedicatedServer() && FSlateApplication::IsInitialized() )
	{
		// Load for cooker reference
		const UCustomLoadingScreenSettings* Settings = GetDefault<UCustomLoadingScreenSettings>();
		for ( const FStringAssetReference& Ref : Settings->StartupScreen.Images )
		{
			Ref.TryLoad();
		}

		for ( const FStringAssetReference& Ref : Settings->DefaultScreen.Images )
		{
			Ref.TryLoad();
		}

		//if (IsMoviePlayerEnabled())
		//{
		//	GetMoviePlayer()->OnPrepareLoadingScreen().AddRaw(this, &FCustomLoadingScreenModule::HandlePrepareCustomLoadingScreen);
		//}

		// Prepare the startup screen, the PrepareCustomLoadingScreen callback won't be called
		// if we've already explictly setup the loading screen.
		if (IsMoviePlayerEnabled())
		{
			ShowLoadingScreen(Settings->StartupScreen);
		}
	}
}

void FCustomLoadingScreenModule::ShutdownModule()
{
	//if ( !IsRunningDedicatedServer() )
	//{
	//	GetMoviePlayer()->OnPrepareLoadingScreen().RemoveAll(this);
	//}

#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings(
			"Project",
			"LodingScreen",
			"LodingScreenSetting"
		);
	}
#endif
}

void FCustomLoadingScreenModule::StartLoadingScreen(bool bOverrideAttributes, FOverrideAttributes Attributes)
{
	const UCustomLoadingScreenSettings*Settings = GetDefault<UCustomLoadingScreenSettings>();
	FCustomLoadingScreenDescription DefaultScreenSettings = Settings->DefaultScreen;

	if (bOverrideAttributes)
	{
		DefaultScreenSettings.MinimumLoadingScreenDisplayTime = Attributes.MinimumLoadingScreenDisplayTime;
		DefaultScreenSettings.bAutoCompleteWhenLoadingCompletes = Attributes.bAutoCompleteWhenLoadingCompletes;
		DefaultScreenSettings.bWaitForManualStop = Attributes.bWaitForManualStop;
		DefaultScreenSettings.PlaybackType = Attributes.PlaybackType;
	}

	ShowLoadingScreen(DefaultScreenSettings);
}

void FCustomLoadingScreenModule::StopLoadingScreen()
{
	GetMoviePlayer()->StopMovie();
}

//void FCustomLoadingScreenModule::HandlePrepareCustomLoadingScreen()
//{
//	const UCustomLoadingScreenSettings* Settings = GetDefault<UCustomLoadingScreenSettings>();
//	BeginCustomLoadingScreen(Settings->DefaultScreen);
//}

void FCustomLoadingScreenModule::ShowLoadingScreen(const FCustomLoadingScreenDescription& ScreenDescription)
{
	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.MinimumLoadingScreenDisplayTime = ScreenDescription.MinimumLoadingScreenDisplayTime;
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = ScreenDescription.bAutoCompleteWhenLoadingCompletes;
	LoadingScreen.bMoviesAreSkippable = ScreenDescription.bMoviesAreSkippable;
	LoadingScreen.bWaitForManualStop = ScreenDescription.bWaitForManualStop;
	LoadingScreen.MoviePaths = ScreenDescription.MoviePaths;
	LoadingScreen.PlaybackType = ScreenDescription.PlaybackType;
	
	if (ScreenDescription.bShowUIOverlay)
	{
		LoadingScreen.WidgetLoadingScreen = SNew(SCustomLoadingScreen, ScreenDescription);
	}

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}


#undef LOCTEXT_NAMESPACE
