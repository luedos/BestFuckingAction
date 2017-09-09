// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Enemy_Char.h"


// Sets default values
AEnemy_Char::AEnemy_Char()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Team = ETeamEnum::TE_Enemy;

	IsInDelay = false;
}

// Called when the game starts or when spawned
void AEnemy_Char::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Char::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}



void AEnemy_Char::StartEnemyDelay(float InDelay)
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		if (World->GetTimerManager().IsTimerActive(EnemyDelayTimer))
			World->GetTimerManager().ClearTimer(EnemyDelayTimer);

		IsInDelay = true;

		World->GetTimerManager().SetTimer(EnemyDelayTimer, this, &AEnemy_Char::StopEnemyDelay, InDelay);
	}

}

void AEnemy_Char::StopEnemyDelay()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
		if (World->GetTimerManager().IsTimerActive(EnemyDelayTimer))
			World->GetTimerManager().ClearTimer(EnemyDelayTimer);

	IsInDelay = false;
}








void AEnemy_Char::EnemyFire_Implementation(int NumberOfFire, AActor* Target, bool ShootWhileVisible)
{}

