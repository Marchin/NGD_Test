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
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	virtual void Destroyed() override;
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* DestructionSound;

	UFUNCTION(BlueprintPure)
	UMaterialInterface* GetMaterial() const;

	UFUNCTION(BlueprintPure)
	FVector GetSize() const;

	UFUNCTION(BlueprintCallable)
	void SetMaterial(UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable)
	void SetMeshRotation(FRotator Rotation);

	UFUNCTION()
	void UpdateMesh();

	UFUNCTION()
	void WasHit(APlayerState* Player, int32 ChainNum);
private:
	UPROPERTY(ReplicatedUsing = UpdateMesh)
	UMaterialInterface* ElementMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, replicated, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ElementMesh;

	UFUNCTION()
	void CheckSidesForCombo(FVector Direction);

	UPROPERTY()
	APlayerState* WhoHitIt;

	UPROPERTY()
	int32 ChainNumber;
};
