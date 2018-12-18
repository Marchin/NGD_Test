// Fill out your copyright notice in the Description page of Project Settings.

#include "NGD_TestGameState.h"
#include "EngineUtils.h"
#include "Pyramid.h"
#include "UnrealNetwork.h"
#include "Engine.h"

void ANGD_TestGameState::ElementWasDestroyed()
{
	TotalElements--;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("%d"), TotalElements));
	if (TotalElements <= 0) 
	{
		GameOver.Broadcast();
	}
}

void ANGD_TestGameState::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<APyramid> iPyramid(GetWorld()); iPyramid; ++iPyramid) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("YOHHO")));
		TotalElements += iPyramid->GetElementsAmount();
	}
}

void ANGD_TestGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANGD_TestGameState, GameOver);
}