// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NGD_TestGameMode.h"
#include "NGD_TestHUD.h"
#include "NGD_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "NGD_Test_PS.h"
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

void ANGD_TestGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	IDCount = 0;
}

void ANGD_TestGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ANGD_Test_PS* State = Cast<ANGD_Test_PS>(NewPlayer->PlayerState);
	if (State)
	{
		State->SetID(IDCount++);
	}
}
