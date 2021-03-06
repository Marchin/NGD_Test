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
	UFUNCTION(BlueprintPure, Category = "NGD")
	int32 GetScore() const;

	UFUNCTION(BlueprintPure, Category = "NGD")
	int32 GetID() const;

	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void MulticastSetID(int32 ID);
	void MulticastSetID_Implementation(int32 ID);
	bool MulticastSetID_Validate(int32 ID);

	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void MulticastAddPoints(int32 Points);
	void MulticastAddPoints_Implementation(int32 Points);
	bool MulticastAddPoints_Validate(int32 Points);

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	virtual void BeginPlay() override;
private:
	UPROPERTY(replicated)
	int32 NGD_Score;

	UPROPERTY(replicated)
	int32 NGD_ID;
};
