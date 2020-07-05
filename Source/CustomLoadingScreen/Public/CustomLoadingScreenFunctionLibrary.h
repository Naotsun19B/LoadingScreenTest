// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomLoadingScreenSettings.h"
#include "CustomLoadingScreenFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMLOADINGSCREEN_API UCustomLoadingScreenFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "LoadingScreen")
	static bool StartLoadingScreen();

	UFUNCTION(BlueprintCallable, Category = "LoadingScreen")
	static bool StartLoadingScreenWithOverrideAttributes(FOverrideAttributes Attributes);

	UFUNCTION(BlueprintCallable, Category = "LoadingScreen")
	static bool StopLoadingscreen();
};
