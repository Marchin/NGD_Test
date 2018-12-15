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

void ANGD_TestGameMode::Register(ANGD_TestCharacter* Player)
{
	PlayerScores.Add(Player, 0);
}

int32 ANGD_TestGameMode::GetScore(ANGD_TestCharacter* Player) 
{
	return PlayerScores[Player];
}

void ANGD_TestGameMode::AddScore(ANGD_TestCharacter* Player, int32 Points)
{
	PlayerScores[Player] += Points;
}
