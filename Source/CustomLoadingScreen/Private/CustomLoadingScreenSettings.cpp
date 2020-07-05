// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomLoadingScreenSettings.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Font.h"

#define LOCTEXT_NAMESPACE "CustomLoadingScreen"

FCustomLoadingScreenDescription::FCustomLoadingScreenDescription()
	: LoadingText(LOCTEXT("Loading", "LOADING"))
{
}

UCustomLoadingScreenSettings::UCustomLoadingScreenSettings(const FObjectInitializer& Initializer)
	: Super(Initializer)
{
	TipWrapAt = 1000.0f;

	if ( !IsRunningDedicatedServer() )
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		TipFont = FSlateFontInfo(RobotoFontObj.Object, 20, FName("Normal"));
		LoadingFont = FSlateFontInfo(RobotoFontObj.Object, 32, FName("Bold"));
	}
}

#undef LOCTEXT_NAMESPACE
