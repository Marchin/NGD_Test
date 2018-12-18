// Fill out your copyright notice in the Description page of Project Settings.

#include "NGD_Test_PS.h"
#include "UnrealNetwork.h"
#include "Engine.h"


void ANGD_Test_PS::BeginPlay()
{
	Super::BeginPlay();
	bReplicates = true;
}

int32 ANGD_Test_PS::GetScore() const
{
	return NGD_Score;
}

int32 ANGD_Test_PS::GetID() const
{
	return NGD_ID;
}

void ANGD_Test_PS::SetID_Implementation(int32 ID)
{
	NGD_ID = ID;
}

bool ANGD_Test_PS::SetID_Validate(int32 ID)
{
	return true;
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
	DOREPLIFETIME(ANGD_Test_PS, NGD_ID);
}
