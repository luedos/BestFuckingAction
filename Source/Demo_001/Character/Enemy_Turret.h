// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Enemy_Char.h"
#include "Enemy_Turret.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API AEnemy_Turret : public AEnemy_Char
{
	GENERATED_BODY()

public:

	AEnemy_Turret();

		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Turret)
		void SetOpen(bool InState);
	
	
};
