// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NGD_TestGameState.generated.h"

/**
 * 
 */
UCLASS()
class NGD_TEST_API ANGD_TestGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	//UFUNCTION()
	//void Register(class ANGD_TestCharacter* Player);

	//UFUNCTION()
	//void AddScore(class ANGD_TestCharacter* Player, int32 Points);


	//UFUNCTION(BlueprintPure, Category = "NGD_Test")
	//int32 GetScore(class ANGD_TestCharacter* Player);

protected:


private:
	UPROPERTY()
	TMap<class ANGD_TestCharacter*, int32> PlayerScores;
	
	
};
