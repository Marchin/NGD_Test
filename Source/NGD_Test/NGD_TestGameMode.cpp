// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NGD_TestGameMode.h"
#include "NGD_TestHUD.h"
#include "NGD_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "NGD_Test_PS.h"

ANGD_TestGameMode::ANGD_TestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANGD_TestHUD::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
}

void ANGD_TestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ANGD_Test_PS* State = Cast<ANGD_Test_PS>(NewPlayer->PlayerState);
	if (State)
	{
		State->MulticastSetID(GetNumPlayers());
	}
}

AActor* ANGD_TestGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	//We want to occupy all PlayerStarts before repeating
	return PlayerStarts[GetNumPlayers()%PlayerStarts.Num()];
}
