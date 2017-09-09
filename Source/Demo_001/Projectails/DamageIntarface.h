// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DamageIntarface.generated.h"

/**
 * 
 */
UENUM(BlueprintType)		
enum class EDamageType : uint8
{
	VE_Bullet 		UMETA(DisplayName = "Bullet"),
	VE_ShotGun		UMETA(DisplayName = "ShotGun"),
	VE_LaserBeam	UMETA(DisplayName = "LaserBeam")
};

UINTERFACE(BlueprintType) class DEMO_001_API UDamageIntarface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IDamageIntarface
{
	GENERATED_IINTERFACE_BODY()

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Damage)
		void DoDamage(float Damage, APlayerController* CallInstigator, AActor* Couser, EDamageType DamageType);


};