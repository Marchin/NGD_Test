// Fill out your copyright notice in the Description page of Project Settings.

#include "PyramidElement.h"
#include <Classes/Components/StaticMeshComponent.h>
#include <Classes/Materials/Material.h>

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

// Called every frame
void APyramidElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APyramidElement::SetMaterial(UMaterialInterface* material)
{
	ElementMesh->SetMaterial(0, material);
}

