// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Shield.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class DEMO_001_API UShield : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:

	UShield();

	UFUNCTION(BlueprintCallable, Category = OnCreated)
	void OnCreated(ACharacter* CharRef);

	UFUNCTION(BlueprintNativeEvent, Category = OnCreated)
	void OnCreatedBNE();
	virtual void OnCreatedBNE_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Destroy)
	void OnDestroyBNE();
	virtual void OnDestroyBNE_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Destroy)
	void OnDownBNE();
	virtual void OnDownBNE_Implementation();

	UFUNCTION(BlueprintCallable, Category = HP)
	void RemoveHP(float HPToRemove);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Char)
	float SpeedNerf;



protected:

	UPROPERTY(BlueprintReadOnly, Category = Char)
	ACharacter* Char;

	UPROPERTY(BlueprintReadOnly, Category = Char)
	float CharWalkSpeed;


private:

	float ShieldHP;



};
