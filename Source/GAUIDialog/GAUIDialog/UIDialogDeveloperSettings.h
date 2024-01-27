// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DeveloperSettings.h"

#include "UIDialogDeveloperSettings.generated.h"


/**
 * Settings for a loading screen system.
 */
UCLASS(Config = "Game", Defaultconfig, meta = (DisplayName = "Game UI: Dialog Addon"))
class UUIDialogDeveloperSettings : public UDeveloperSettings
{
public:
	GENERATED_BODY()
public:
	UUIDialogDeveloperSettings();


	///////////////////////////////////////////////
	// Dialog
public:
	UPROPERTY(Config, EditAnywhere, Category = "Dialog", meta = (MetaClass = "/Script/GAUIDialog.UIDialog"))
	FSoftClassPath ConfirmationDialogClass;

	UPROPERTY(Config, EditAnywhere, Category = "Dialog", meta = (MetaClass = "/Script/GAUIDialog.UIDialog"))
	FSoftClassPath ErrorDialogClass;

};

