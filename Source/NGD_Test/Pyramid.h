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
	// Sets default values for this actor's properties
	APyramid();

	UPROPERTY(EditAnywhere, Category = "Pyramid")
		TArray<UMaterialInterface*> Materials;

	UPROPERTY(EditAnywhere, Category = "Pyramid")
		TSubclassOf<APyramidElement> ElementBP;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TArray<APyramidElement*> Elements;

	UPROPERTY(EditAnywhere, Category = "Pyramid")
	uint8 NumberOfRows;

	UPROPERTY()
		uint8 ElementsAmount;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
