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

	UPROPERTY(EditAnywhere, replicated, Category = "Pyramid")
		TArray<UMaterialInterface*> Materials;

	UPROPERTY(EditAnywhere, replicated, Category = "Pyramid")
		TSubclassOf<APyramidElement> ElementBP;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UFUNCTION(Reliable, Server, WithValidation)
	void SetupPyramid();
	void SetupPyramid_Implementation();
	bool SetupPyramid_Validate();

	UPROPERTY(replicated)
	TArray<APyramidElement*> Elements;

	UPROPERTY(EditAnywhere, Category = "Pyramid")
	uint8 NumberOfRows;

	UPROPERTY()
	uint8 ElementsAmount;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
