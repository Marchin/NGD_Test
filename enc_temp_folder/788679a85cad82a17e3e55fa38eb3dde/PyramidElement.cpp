// Fill out your copyright notice in the Description page of Project Settings.

#include "PyramidElement.h"
#include <Classes/Components/StaticMeshComponent.h>
#include <Classes/Materials/Material.h>
#include "Engine/World.h"
#include "NGD_Test_PS.h"
#include "CustomMath.h"
#include "UnrealNetwork.h"

// Sets default values
APyramidElement::APyramidElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Element Mesh")); 
	ElementMesh->SetIsReplicated(true);
	RootComponent = ElementMesh;
	bReplicates = true;
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
		float Points = CustomMath::Fibonacci(ChainNumber);
		ANGD_Test_PS* Player = Cast<ANGD_Test_PS>(WhoHitIt);
		if (Player)
		{
			Player->AddPoints(Points);
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

UMaterialInterface * APyramidElement::GetMaterial() const
{
	return ElementMesh->GetMaterial(0);
}

void APyramidElement::SetMaterial_Implementation(UMaterialInterface* Material)
{
	ElementMaterial = Material;
	ElementMesh->SetMaterial(0, ElementMaterial);
}

bool APyramidElement::SetMaterial_Validate(UMaterialInterface * Material)
{
	return true;
}

void APyramidElement::WasHit(APlayerState* PlayerID, int32 ChainNum)
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

void APyramidElement::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APyramidElement, ElementMesh);
	DOREPLIFETIME(APyramidElement, ElementMaterial);
}

