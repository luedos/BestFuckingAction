// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_DistanceToActorSet.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API UEnvQueryTest_DistanceToActorSet : public UEnvQueryTest
{
	GENERATED_BODY()
	
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
	
	
};
