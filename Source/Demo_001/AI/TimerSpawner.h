// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Spawner.h"
#include "ParticleDefinitions.h"
#include "TimerSpawner.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API ATimerSpawner : public ASpawner
{
	GENERATED_BODY()
	
public:

	ATimerSpawner() : SpawnRate(1), RandomInRate(0) {}

	UFUNCTION(BlueprintCallable, Category = Spawn)
	void Spawn() override;
	
protected:
	UFUNCTION(BlueprintCallable, Category = Spawn)
	void AfterSpawn(int NumberOfSpawned) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawn)
	float SpawnRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawn)
	float RandomInRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawn)
	int NumberOfSpawn = 0;

private:

	FTimerHandle SpawnTimer;

	int LocalSpawnNumber;
};
