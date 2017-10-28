// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "TimerSpawner.h"



void ATimerSpawner::Spawn()
{
	UWorld* World = GetWorld();

	if (World != NULL)
	{
		if (World->GetTimerManager().IsTimerActive(SpawnTimer))
			World->GetTimerManager().ClearTimer(SpawnTimer);
		LocalSpawnNumber = 0;
		ExecuteSpawn();
	}
}


void ATimerSpawner::AfterSpawn(int NumberOfSpawned)
{
	UWorld* World = GetWorld();

	if (World != NULL)
	{
		float Rand = FMath::FRandRange(0, RandomInRate);

		if (NumberOfSpawn != 0)
		{
			LocalSpawnNumber++;
			if (LocalSpawnNumber >= NumberOfSpawn)
				World->GetTimerManager().SetTimer(SpawnTimer, this, &ASpawner::ExecuteSpawn, SpawnRate + Rand, false, SpawnRate + Rand);
		}
		else
		{
			World->GetTimerManager().SetTimer(SpawnTimer, this, &ASpawner::ExecuteSpawn, SpawnRate + Rand, false, SpawnRate + Rand);
		}
	}
}