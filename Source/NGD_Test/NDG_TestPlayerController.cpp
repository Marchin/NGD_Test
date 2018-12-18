// Fill out your copyright notice in the Description page of Project Settings.

#include "NDG_TestPlayerController.h"
#include "NGD_TestGameState.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "Engine.h"

void ANDG_TestPlayerController::Disable_Implementation()
{
	if (HighScoreWidget != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HighScoreWidget);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

bool ANDG_TestPlayerController::Disable_Validate()
{
	return true;
}

void ANDG_TestPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bReplicates = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("NO"));
	ANGD_TestGameState* GameState =	GetWorld()->GetGameState<ANGD_TestGameState>();
	if (GameState)
	{
		GameState->GameOver.AddDynamic(this, &ANDG_TestPlayerController::Disable);
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FAIL"));
	}
}
