// Fill out your copyright notice in the Description page of Project Settings.

#include "NGD_TestGameState.h"
#include "EngineUtils.h"
#include "Pyramid.h"
#include "NGD_Test_PS.h"
#include "UnrealNetwork.h"
#include "Engine.h"

void ANGD_TestGameState::ElementWasDestroyed()
{
	TotalElements--;
	if (bGameStarted && TotalElements <= 0)
	{ 
		//INVESTIGATE: look for a function that does not neet a time handler
		//Delay so clients are notified of points from the last hit
		GetWorldTimerManager().SetTimer(Timer, this, &ANGD_TestGameState::MulticastEndMatch, .5f, false);
	}
}

void ANGD_TestGameState::MulticastEndMatch_Implementation()
{
	PlayerArray.Sort([](APlayerState& StateA, APlayerState& StateB)
		{
			ANGD_Test_PS* NGDStateA = Cast<ANGD_Test_PS>(&StateA);
			ANGD_Test_PS* NGDStateB = Cast<ANGD_Test_PS>(&StateB);
			if (NGDStateA && NGDStateB)
			{
				return (NGDStateA->GetScore() > NGDStateB->GetScore());
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Invalid State")));
				return false;
			}
		});
	GameOver.Broadcast();
}

bool ANGD_TestGameState::MulticastEndMatch_Validate()
{
	return true;
}

void ANGD_TestGameState::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<APyramid> iPyramid(GetWorld()); iPyramid; ++iPyramid)
	{
		iPyramid->SetupPyramid();
		TotalElements += iPyramid->GetElementsAmount();
	}
	bGameStarted = true;
}
