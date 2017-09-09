// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"
#include "CoverArrow.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DEMO_001_API UCoverArrow : public UArrowComponent
{
	GENERATED_BODY()
	
public:

	UCoverArrow();

	UFUNCTION(BlueprintPure, Category = CoverSpot)
	bool GetOccupiedStatus();

	UFUNCTION(BlueprintCallable, Category = CoverSpot)
	void ChangeOccupiedStatus(bool NewStatus);

	UPROPERTY(BlueprintReadWrite, Category = CoverSpot)
	AActor* EnemyWhichOccupy;

private:

	bool IsOccupied;
	
};
