// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NDG_TestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NGD_TEST_API ANDG_TestPlayerController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION(Reliable, Client, WithValidation)
	void Disable();
	void Disable_Implementation();
	bool Disable_Validate();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NGD_Test")
		TSubclassOf<class UUserWidget> HighScoreWidget;
	UPROPERTY()
		class UUserWidget* CurrentWidget;

protected:
	virtual void BeginPlay() override;
};
