// Fill out your copyright notice in the Description page of Project Settings.

#include "Pyramid.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "Engine.h"

//       _				The pyramid follows the structure 1-3-3-5-5... from top to bottom.
//     _|_|_			To achieve this we make use of the truncation that happens when dividing 2 integers.
//    |_|_|_|			That way we can add one element at each side every 2 rows.
//   _|_|_|_|_			The algorithm starts with an offset of one so there is only a one-element row, achieving a better pyramidal shape.
//  |_|_|_|_|_|
// _|_|_|_|_|_|_
//|_|_|_|_|_|_|_|

APyramid::APyramid()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
}

void APyramid::BeginPlay()
{
	Super::BeginPlay();
}

int32 APyramid::GetElementsAmount()
{
	return ElementsAmount;
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
	if (!bAlreadySetup && Role == ROLE_Authority)
	{
		ElementsAmount = 0;
		for (int32 i = 0; i < NumberOfRows; i++)
		{
			ElementsAmount += 1 + (2 * ((i + 1) / 2));
		}
		Elements.Reserve(ElementsAmount);
		FVector RootLocation = GetActorLocation();
		for (int32 i = 0; i < NumberOfRows; i++)
		{
			uint8 ColumnsInRow = 1 + (2 * ((NumberOfRows - i) / 2));	//from bottom to top
																		//"1 + ..." so theres is only a one-element row 
			for (uint8 j = 0; j < ColumnsInRow; j++)
			{
				FVector Position(GetActorRightVector());
				APyramidElement* NewElement;
				if (i == 0 && j == 0)	//We first spawn the bottom-middle element and we measure it so we know the offset of the elements.
										//We tried to use CDO but it would only work In-Editor from the second time onwards,
										//probably due to how Unreal manages serialization and reflection
				{
					NewElement = GetWorld()->SpawnActor<APyramidElement>(ElementBP, RootLocation, FRotator::ZeroRotator);
					Distance = NewElement->GetSize();
					NewElement->SetMeshRotation(GetActorRotation());
				}
				else
				{
					Position *= ((j + 1)/2)*(((j+1)%2)*2 - 1);	//Sideways offset
																//First column has offset 0, 2nd & 3rd (-1;1) and so on.
					Position.Z = (i);
					Position *= Distance;
					Position += RootLocation;
					NewElement = GetWorld()->SpawnActor<APyramidElement>(ElementBP, Position, GetActorRotation());
				}
				NewElement->SetMaterial(Materials[FMath::RandRange(0, Materials.Num() - 1)]);
				Elements.Push(NewElement);
			}
		}
		bAlreadySetup = true;
	}
}

