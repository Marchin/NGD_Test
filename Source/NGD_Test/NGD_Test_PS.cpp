// Fill out your copyright notice in the Description page of Project Settings.

#include "NGD_Test_PS.h"

int32 ANGD_Test_PS::GetScore()
{
	return NGD_Score;
}

void ANGD_Test_PS::AddPoints(int32 Points)
{
	NGD_Score += Points;
}
