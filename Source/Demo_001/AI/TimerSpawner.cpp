// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "TimerSpawner.h"



void ATimerSpawner::Spawn()
{
	UWorld* World = GetWorld();

	if (World != NULL)
	{
		LocalSpawnNumber = 0;
		if (World->GetTimerManager().IsTimerActive(SpawnTimer))
			World->GetTimerManager().ClearTimer(SpawnTimer);
		World->GetTimerManager().SetTimer(SpawnTimer, this, &ASpawner::ExecuteSpawn, SpawnRate, true, 0.f);
	}
}


void ATimerSpawner::AfterSpawn(int NumberOfSpawned)
{
	if (NumberOfSpawn != 0)
	{
		LocalSpawnNumber++;
		if (LocalSpawnNumber >= NumberOfSpawn)
			GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}