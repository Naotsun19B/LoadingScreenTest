// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Widgets/SCompoundWidget.h"
#include "CustomLoadingScreenSettings.h"

class FDeferredCleanupSlateBrush;

class SCustomLoadingScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SCustomLoadingScreen) {}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FCustomLoadingScreenDescription& ScreenDescription);

private:
	float GetDPIScale() const;
	
private:
	TSharedPtr<FDeferredCleanupSlateBrush> LoadingScreenBrush;
};
