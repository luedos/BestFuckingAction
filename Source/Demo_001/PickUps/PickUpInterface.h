// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Character/CharPawn.h"
#include "PickUpInterface.generated.h"
/**
 * 
 */

UINTERFACE(BlueprintType) class DEMO_001_API UPickUpInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IPickUpInterface
{
	GENERATED_IINTERFACE_BODY()

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = PickUp)
		void PickUpFunc(ACharPawn* FromChar);
	


};

