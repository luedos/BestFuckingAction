// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/CharSkills/Object_Skills.h"
#include "Object_Skills_NormalMelee.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API UObject_Skills_NormalMelee : public UObject_Skills
{
	GENERATED_BODY()

public:
	
	virtual void UseSkill_Implementation(ACharacter* Char, float FloatA, float FloatB, FVector Vector) override;
	
	
	
};
