// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NGD_Test_PS.generated.h"

/**
 * 
 */
UCLASS()
class NGD_TEST_API ANGD_Test_PS : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(Reliable, Server, WithValidation)
	void AddPoints(int32 Points);
	void AddPoints_Implementation(int32 Points);
	bool AddPoints_Validate(int32 Points);

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

private:
	UPROPERTY(replicated)
	int32 NGD_Score;
};
