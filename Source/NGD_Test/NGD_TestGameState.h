// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NGD_TestGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOver);
UCLASS()
class NGD_TEST_API ANGD_TestGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Pyramid")
	void ElementWasDestroyed();

	UPROPERTY(BlueprintAssignable, /*replicated,*/ Category = "Pyramid")
	FGameOver GameOver;
protected:
	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void MulticastEndMatch();
	void MulticastEndMatch_Implementation();
	bool MulticastEndMatch_Validate();
	virtual void BeginPlay() override;
	//virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UPROPERTY()
	FTimerHandle GameOverTimer;
private:
	UPROPERTY()
	int32 TotalElements;

};
