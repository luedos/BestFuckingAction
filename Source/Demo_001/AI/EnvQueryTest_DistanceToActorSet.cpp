// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "EnvQueryTest_DistanceToActorSet.h"

void UEnvQueryTest_DistanceToActorSet::RunTest(FEnvQueryInstance & QueryInstance) const
{
}

FText UEnvQueryTest_DistanceToActorSet::GetDescriptionTitle() const
{
	return  FText::FromString("FIND SOLDIER");
}

FText UEnvQueryTest_DistanceToActorSet::GetDescriptionDetails() const
{
	return FText::FromString("SOldier test");
}
