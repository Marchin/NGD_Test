// Fill out your copyright notice in the Description page of Project Settings.

#include "Pyramid.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "Engine.h"

//       _
//     _|_|_
//    |_|_|_|
//   _|_|_|_|_
//  |_|_|_|_|_|
// _|_|_|_|_|_|_
//|_|_|_|_|_|_|_|

// Sets default values
APyramid::APyramid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
}

int32 APyramid::GetElementsAmount()
{
	return ElementsAmount;
}

// Called when the game starts or when spawned
void APyramid::BeginPlay()
{
	Super::BeginPlay();
	SetupPyramid();
}

void APyramid::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APyramid, Materials);
	DOREPLIFETIME(APyramid, Elements);
	DOREPLIFETIME(APyramid, ElementBP);
}

void APyramid::SetupPyramid()
{
	if (Role == ROLE_Authority)
	{
		ElementsAmount = 0;
		for (int32 i = 0; i < NumberOfRows; i++)
		{
			ElementsAmount += 1 + (2 * ((i + 1) / 2));
		}
		Elements.Reserve(ElementsAmount);
		APyramidElement* NewElement = GetWorld()->SpawnActor<APyramidElement>(ElementBP); //Find a way to avoid the spawn in order to get Distance
		FVector Distance = NewElement->GetComponentsBoundingBox().GetExtent() * 2.05f;
		NewElement->Destroy();
		FVector RootLocation = GetActorLocation();

		for (int32 i = 0; i < NumberOfRows; i++)
		{
			uint8 ColumnsInRow = 1 + (2 * ((i + 1) / 2));
			for (uint8 j = 0; j < ColumnsInRow; j++)
			{
				FVector Position(GetActorForwardVector());

				Position *= (j - ColumnsInRow * 0.5f);
				Position.Z = (NumberOfRows - i);
				Position *= Distance;
				Position += RootLocation;
				APyramidElement* NewElement = GetWorld()->SpawnActor<APyramidElement>(ElementBP, Position, GetActorRotation());
				NewElement->SetMaterial(Materials[FMath::RandRange(0, Materials.Num() - 1)]);
				Elements.Push(NewElement);
			}
		}
	}
}

// Called every frame
void APyramid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


