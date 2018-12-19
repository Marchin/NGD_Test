// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "GameFramework/GameModeBase.h"
#include "NGD_TestGameMode.generated.h"

UCLASS(minimalapi)
class ANGD_TestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANGD_TestGameMode();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	int32 IDCount;
};



