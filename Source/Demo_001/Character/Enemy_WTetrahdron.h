// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Enemy_Char.h"
#include "Enemy_WTetrahdron.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API AEnemy_WTetrahdron : public AEnemy_Char
{
	GENERATED_BODY()
	


public:
	AEnemy_WTetrahdron();



	
	UFUNCTION(BlueprintCallable, Category = AISkills)
	void StartDesh(FVector PointToDeshRef);

	void DeshCicle();

	void StopDesh();

	UFUNCTION(BlueprintNativeEvent, Category = Test)
	void TestFunction();
	virtual void TestFunction_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = Test)
		void StartDeshBNE(FVector PointDeshRef);
	virtual void StartDeshBNE_Implementation(FVector PointDeshRef);


	UFUNCTION(BlueprintNativeEvent, Category = Test)
		void StopDeshBNE();
	virtual void StopDeshBNE_Implementation();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Test)
	float Coefficient;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Test)
	TArray<float> LengthsArray;

private:

	FTimerHandle DeshTimer;

	float DeshLength;
	float DeshTime;
	int NumberOfSmallDeshes;
	int CountOfSmallDeshes;
	float ASinConst;
	float BSinConst;
	float SinHight;
	float StartDeshSpeed;

	float ArraySum;


	FVector PointToDesh;




};
