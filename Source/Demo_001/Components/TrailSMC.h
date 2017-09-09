// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TrailSMC.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DEMO_001_API UTrailSMC : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UTrailSMC();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	


	UFUNCTION(BlueprintCallable, Category = Trail)
	void StartTimer(float LifeTime, UTrail30* TrailComponentReference);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		FLinearColor StartSMCColor;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		FLinearColor EndSMCColor;

	FVector StartScale;
	FVector EndScale;

protected:

	FTimerHandle DestroyTimer;

	void DestroySMC();

	UTrail30* TrailComponent;

	float Period;

	UMaterialInstanceDynamic* Mat;
	float SMCLifeTime;
};
