// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NGD_TestGameMode.generated.h"

UCLASS(minimalapi)
class ANGD_TestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANGD_TestGameMode();

	UFUNCTION()
	void Register(class ANGD_TestCharacter* Player);

	UFUNCTION()
	void AddScore(class ANGD_TestCharacter* Player, int32 Points);


	UFUNCTION(BlueprintPure, Category = "NGD_Test")
	int32 GetScore(class ANGD_TestCharacter* Player);

private:
	UPROPERTY()
	TMap<class ANGD_TestCharacter*, int32> PlayerScores;

};



