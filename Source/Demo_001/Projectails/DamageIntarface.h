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

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETeamEnum : uint8
{
	TE_Player 	UMETA(DisplayName = "Player"),
	TE_Enemy 	UMETA(DisplayName = "Enemy"),
	TE_Neutral	UMETA(DisplayName = "Neutral")
};

UINTERFACE(BlueprintType) class DEMO_001_API UDamageIntarface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IDamageIntarface
{
	GENERATED_IINTERFACE_BODY()

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Damage)
		void DoDamage(float Damage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType);
		//void DoDamage(float Damage, APlayerController* CallInstigator, AActor* Couser, EDamageType DamageType);


};