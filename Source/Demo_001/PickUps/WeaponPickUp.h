// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUps/PickUp.h"
#include "WeaponPickUp.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API AWeaponPickUp : public APickUp
{


	GENERATED_BODY()

public:

	AWeaponPickUp();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


	
	
	
};
