// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PyramidElement.h"
#include "Pyramid.generated.h"

UCLASS()
class NGD_TEST_API APyramid : public AActor
{
	GENERATED_BODY()
	
public:	
	APyramid();

	UFUNCTION()
	void SetupPyramid();

	UFUNCTION(BlueprintPure)
	int32 GetElementsAmount();

	UPROPERTY(EditAnywhere, replicated, Category = "Pyramid")
	TArray<UMaterialInterface*> Materials;

	UPROPERTY(EditAnywhere, replicated, Category = "Pyramid")
	TSubclassOf<APyramidElement> ElementBP;
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(replicated)
	TArray<APyramidElement*> Elements;

	UPROPERTY(EditAnywhere, Category = "Pyramid")
	int32 NumberOfRows;

	UPROPERTY()
	int32 ElementsAmount; 
	
	UPROPERTY()
	FVector Distance;

	UPROPERTY()
	bool bAlreadySetup;
};
