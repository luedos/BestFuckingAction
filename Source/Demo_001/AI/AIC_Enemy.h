// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "AIC_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API AAIC_Enemy : public AAIController
{
	GENERATED_BODY()

public:

		AAIC_Enemy();


		UFUNCTION(BlueprintCallable, Category = AIVariables)
		void ChangePercepion(bool IsChangeSightRadius, float SightRadius, bool IsChangeLoseRadius, float LoseRadius, bool IsChangeViewAngle, float ViewAngle);

		UFUNCTION(BlueprintPure, Category = AIVariables)
		float GetPerceptionSightRadius();
		UFUNCTION(BlueprintPure, Category = AIVariables)
		float GetPerceptionLoseRadius();
		UFUNCTION(BlueprintPure, Category = AIVariables)
		float GetPerceptionViewAngle();


protected:


	class UAISenseConfig_Sight* Sight;



	UPROPERTY(EditAnywhere, Category = AIVariables)
		UAIPerceptionComponent* PerceptionComp;
	
	
};
