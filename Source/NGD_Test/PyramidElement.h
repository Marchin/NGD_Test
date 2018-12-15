// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PyramidElement.generated.h"

UCLASS()
class NGD_TEST_API APyramidElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APyramidElement();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetMaterial();

	UFUNCTION(BlueprintCallable)
	void SetMaterial(UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable)
	void WasHit(APlayerState* Player, int32 ChainNum);
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ElementMesh;
	

	UFUNCTION()
	void CheckSidesForCombo(FVector Direction);

	UPROPERTY()
	APlayerState* WhoHitIt;

	UPROPERTY()
	int32 ChainNumber;
};
