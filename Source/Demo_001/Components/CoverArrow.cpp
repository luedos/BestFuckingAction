// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "CoverArrow.h"

UCoverArrow::UCoverArrow()
{
	IsOccupied = false;
}

bool UCoverArrow::GetOccupiedStatus()
{
	return IsOccupied;
}

void UCoverArrow::ChangeOccupiedStatus(bool NewStatus)
{
	IsOccupied = NewStatus;
}
