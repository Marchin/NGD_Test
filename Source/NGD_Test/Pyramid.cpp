// Fill out your copyright notice in the Description page of Project Settings.

#include "Pyramid.h"
#include "Engine/World.h"

// Sets default values
APyramid::APyramid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APyramid::BeginPlay()
{
	Super::BeginPlay();

	APyramidElement* NewElement = GetWorld()->SpawnActor<APyramidElement>(Element, GetActorLocation(), GetActorRotation());
	NewElement->SetMaterial(Materials[0]);
}

// Called every frame
void APyramid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

