// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NGD_TestGameMode.h"
#include "NGD_TestHUD.h"
#include "NGD_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "NGD_TestCharacter.h"
#include "Engine/World.h"

ANGD_TestGameMode::ANGD_TestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANGD_TestHUD::StaticClass();
}

