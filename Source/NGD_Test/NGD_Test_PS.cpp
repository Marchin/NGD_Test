// Fill out your copyright notice in the Description page of Project Settings.

#include "NGD_Test_PS.h"
#include "UnrealNetwork.h"


void ANGD_Test_PS::BeginPlay()
{
	Super::BeginPlay();

	static int32 ID = 0;
	NGD_ID = ID++;
}

int32 ANGD_Test_PS::GetScore() const
{
	return NGD_Score;
}

int32 ANGD_Test_PS::GetID() const
{
	return NGD_ID;
}

void ANGD_Test_PS::AddPoints_Implementation(int32 Points)
{
	NGD_Score += Points;
}

bool ANGD_Test_PS::AddPoints_Validate(int32 Points)
{
	return true;
}

void ANGD_Test_PS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANGD_Test_PS, NGD_Score);
}
