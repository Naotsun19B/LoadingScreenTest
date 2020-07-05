// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomLoadingScreenFunctionLibrary.h"
#include "CustomLoadingScreen.h"

bool UCustomLoadingScreenFunctionLibrary::StartLoadingScreen()
{
	if (ICustomLoadingScreenModule::IsAvailable())
	{
		ICustomLoadingScreenModule& LoadingScreenModule = ICustomLoadingScreenModule::Get();
		LoadingScreenModule.StartLoadingScreen(false, FOverrideAttributes());

		return true;
	}

	return false;
}

bool UCustomLoadingScreenFunctionLibrary::StartLoadingScreenWithOverrideAttributes(FOverrideAttributes Attributes)
{
	if (ICustomLoadingScreenModule::IsAvailable())
	{
		ICustomLoadingScreenModule& LoadingScreenModule = ICustomLoadingScreenModule::Get();
		LoadingScreenModule.StartLoadingScreen(true, Attributes);

		return true;
	}

	return false;
}

bool UCustomLoadingScreenFunctionLibrary::StopLoadingscreen()
{
	if (ICustomLoadingScreenModule::IsAvailable())
	{
		ICustomLoadingScreenModule& LoadingScreenModule = ICustomLoadingScreenModule::Get();
		LoadingScreenModule.StopLoadingScreen();

		return true;
	}

	return false;
}
