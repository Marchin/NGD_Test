// Fill out your copyright notice in the Description page of Project Settings.

#include "PyramidElement.h"
#include <Classes/Components/StaticMeshComponent.h>
#include <Classes/Materials/Material.h>
#include "Engine/World.h"
#include "NGD_TestGameMode.h"
#include "CustomMath.h"

// Sets default values
APyramidElement::APyramidElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Element Mesh"));
	RootComponent = ElementMesh;
}

// Called when the game starts or when spawned
void APyramidElement::BeginPlay()
{
	Super::BeginPlay();
	
}

void APyramidElement::Destroyed()
{
	if (WhoHitIt != nullptr)
	{
		float points = CustomMath::Fibonacci(ChainNumber);
		ANGD_TestGameMode* GameMode = Cast<ANGD_TestGameMode>(GetWorld()->GetAuthGameMode());
		int a = 0;
		if (GameMode)
		{
			a++;
			GameMode->AddScore(WhoHitIt, points);
		}
		CheckSidesForCombo(GetActorUpVector());
		CheckSidesForCombo(-GetActorUpVector());
		CheckSidesForCombo(GetActorRightVector());
		CheckSidesForCombo(-GetActorRightVector());
	}
}

// Called every frame
void APyramidElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UMaterialInterface * APyramidElement::GetMaterial()
{
	return ElementMesh->GetMaterial(0);
}

void APyramidElement::SetMaterial(UMaterialInterface* material)
{
	ElementMesh->SetMaterial(0, material);
}

void APyramidElement::WasHit(ANGD_TestCharacter* PlayerID, int32 ChainNum)
{
	if (WhoHitIt == nullptr)
	{
		WhoHitIt = PlayerID;
		ChainNumber = ChainNum;
		Destroy();
	}
}

void APyramidElement::CheckSidesForCombo(FVector Direction)
{
	FHitResult Hit;
	float CheckDistance = ElementMesh->Bounds.BoxExtent.GetAbsMax() * 2.f;
	GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() + Direction * CheckDistance, ECollisionChannel::ECC_Visibility);
	APyramidElement *const PyramidElement = Cast<APyramidElement>(Hit.Actor);
	if (PyramidElement && PyramidElement->GetMaterial() == GetMaterial())
	{
		PyramidElement->WasHit(WhoHitIt, ChainNumber + 1);
	}
}


