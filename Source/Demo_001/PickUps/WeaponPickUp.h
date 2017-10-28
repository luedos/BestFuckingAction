// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUps/PickUp.h"
#include "Objects/Weapons/MC_Weapon.h"
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

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = PickUp)
	//	void PickUpFunc(ACharPawn* FromChar);
	void PickUpFunc_Implementation(ACharPawn* FromChar) override;
	
	UPROPERTY(EditAnywhere, Category = Weapon)
	int PickUpAmmo;
	UPROPERTY(EditAnywhere, Category = Weapon)
	int PickUpBackPackAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<UMC_Weapon> WeaponObject;
	
};
