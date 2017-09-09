// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Object_Skills.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DEMO_001_API UObject_Skills : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent)
	void UseSkill(ACharacter* Char, float FloatA, float FloatB, FVector Vector);
	virtual void UseSkill_Implementation(ACharacter* Char, float FloatA, float FloatB, FVector Vector);
	
	
};
