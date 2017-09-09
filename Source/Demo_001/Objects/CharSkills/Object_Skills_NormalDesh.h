// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/CharSkills/Object_Skills.h"
#include "Object_Skills_NormalDesh.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API UObject_Skills_NormalDesh : public UObject_Skills
{
	GENERATED_BODY()

public:

	virtual void UseSkill_Implementation(ACharacter* Char, float FloatA, float FloatB, FVector Vector) override;

	UFUNCTION(BlueprintCallable, Category = Desh)
	void Desh(ACharacter* Char, float SpeedOfDesh, float Distance, FVector Direction);

protected:
	void DeshInProcess();
	FRotator RotToDesh;
	int NumberOfJumps;
	float MySpeedOfDesh;
	float MyDistanse;
	FTimerHandle TimerOfDesh;
	ACharacter* CharToDesh;
	
	
	
};
