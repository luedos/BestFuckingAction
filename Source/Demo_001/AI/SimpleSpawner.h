// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Spawner.h"
#include "SimpleSpawner.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API ASimpleSpawner : public ASpawner
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Spawn)
	void Spawn() override;

protected:

	UFUNCTION(BlueprintCallable, Category = Spawn)
	void AfterSpawn(int NumberOfSpawned) override;
	
	
};
