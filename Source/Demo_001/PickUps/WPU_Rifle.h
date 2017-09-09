// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUps/WeaponPickUp.h"
#include "WPU_Rifle.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API AWPU_Rifle : public AWeaponPickUp
{
	GENERATED_BODY()
	
public:

	AWPU_Rifle();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	
};
