// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NGD_TestHUD.generated.h"

UCLASS()
class ANGD_TestHUD : public AHUD
{
	GENERATED_BODY()

public:
	ANGD_TestHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

