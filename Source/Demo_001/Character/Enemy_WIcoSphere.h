// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Enemy_Char.h"
#include "Components/Shield.h"

#include "Enemy_WIcoSphere.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API AEnemy_WIcoSphere : public AEnemy_Char
{
	GENERATED_BODY()

		public:

		AEnemy_WIcoSphere();

		UFUNCTION(BlueprintCallable, Category = Shield)
		void ShieldUp(float InDelay);

		UFUNCTION(BlueprintCallable, Category = Shield)
		void ShieldDown();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shield)
		TSubclassOf<UShield> UsingShield;



protected:

	UPROPERTY(BlueprintReadOnly, Category = Shield)
	UShield* ShieldComponent;

private:

	FTimerHandle ShieldTimer;


};
