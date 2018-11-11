// Fill out your copyright notice in the Description page of Project Settings.

#include "Pyramid.h"
#include "Engine/World.h"

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
	ElementsAmount = 0;
	for (uint8 i = 0; i < NumberOfRows; i++)
	{
		ElementsAmount += 1 + (2 * ((i + 1)/2));
	}
	Elements.Reserve(ElementsAmount);
}

// Called when the game starts or when spawned
void APyramid::BeginPlay()
{
	Super::BeginPlay();
	APyramidElement* NewElement = GetWorld()->SpawnActor<APyramidElement>(ElementBP); //Find a way to avoid the spawn in order to get Distance
	FVector Distance = NewElement->GetComponentsBoundingBox().GetExtent() * 2.05f;
	NewElement->Destroy();
	FVector RootLocation = GetActorLocation();

	for (uint8 i = 0; i < NumberOfRows; i++)
	{
		uint8 ColumnsInRow = 1 + (2 * ((i + 1) / 2));
		for (uint8 j = 0; j < ColumnsInRow; j++)
		{
			FVector Position(0.f, j - ColumnsInRow * 0.5f, (NumberOfRows - i));
			Position *= Distance;
			Position += RootLocation;
			APyramidElement* NewElement = GetWorld()->SpawnActor<APyramidElement>(ElementBP, Position, GetActorRotation());
			NewElement->SetMaterial(Materials[FMath::RandRange(0, Materials.Num() - 1)]);
			Elements.Push(NewElement);
		}
	}
}

// Called every frame
void APyramid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


