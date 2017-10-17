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


	UFUNCTION(BlueprintImplementableEvent, Category = Test)
		void StartDeshBNE(FVector PointDeshRef);


	UFUNCTION(BlueprintImplementableEvent, Category = Test)
		void StopDeshBNE();


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Ray)
	void StartRay(float PrepareLengthRef, float RayLengthRef, UParticleSystemComponent* ArcParticleRef);

	UFUNCTION(BlueprintPure, Category = Ray)
		bool GetIsCanRay() { return CanRay; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Test)
	float Coefficient;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Test)
	TArray<float> LengthsArray;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Ray)
		void StopRayBNE();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Ray)
		void TestBNE(ETraceTypeQuery InRef);

	UFUNCTION(BlueprintCallable, Category = Ray)
		void StopRayCicle();




protected:
	UFUNCTION(BlueprintCallable, Category = Ray)
		void StartRayCicle(float RayLengthRef);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ray)
		float SetCanRayTrueLength = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ray)
	float RayLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ray)
		float RayDamageRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ray)
		float RayRotSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Ray)
		bool CanRay = true;

	UPROPERTY(EditAnywhere, Category = Ray)
	UParticleSystem* RayParticle;

	UPROPERTY(BlueprintReadWrite, Category = Ray)
		UParticleSystemComponent* ArcParticle;

private:
	void RayCicle();

	FTimerHandle RayTimer;
	void SetTrueCanRay() { CanRay = true; }
	float RayTimeLength;
	UParticleSystemComponent* RayParticleComponent;


	float LocalRotationRate;

	FTimerHandle DeshTimer;

	float RayTime;

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
