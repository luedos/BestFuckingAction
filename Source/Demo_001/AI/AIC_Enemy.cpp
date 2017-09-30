// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "AIC_Enemy.h"



AAIC_Enemy::AAIC_Enemy()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Enemy Perception"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	PerceptionComp->ConfigureSense(*Sight);
	PerceptionComp->SetDominantSense(Sight->GetSenseImplementation());



	
	Sight->SightRadius = 2500;
	Sight->LoseSightRadius = 3000;
	Sight->PeripheralVisionAngleDegrees = 180.0f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	


	// Apply Sight to Perception Component
	PerceptionComp->ConfigureSense(*Sight);
	PerceptionComp->SetDominantSense(Sight->GetSenseImplementation());

}



void AAIC_Enemy::ChangePercepion(bool IsChangeSightRadius, float SightRadius, bool IsChangeLoseRadius, float LoseRadius, bool IsChangeViewAngle, float ViewAngle)
{
	if (IsChangeSightRadius)
	{
		Sight->SightRadius = SightRadius;
	}
	if (IsChangeLoseRadius)
	{
		Sight->LoseSightRadius = LoseRadius;
	}
	if (IsChangeViewAngle)
	{
		Sight->PeripheralVisionAngleDegrees = ViewAngle;
	}
	
}



float AAIC_Enemy::GetPerceptionSightRadius()
{
	return Sight->SightRadius;
}


float AAIC_Enemy::GetPerceptionLoseRadius()
{
	return Sight->LoseSightRadius;
}

float AAIC_Enemy::GetPerceptionViewAngle()
{
	return Sight->PeripheralVisionAngleDegrees;
}