// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Trail30.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO_001_API UTrail30 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrail30();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
	float SpawnDelay;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
	float TrailTimeLength;


	

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
	UMaterial* TrailMaterial;

	UFUNCTION(BlueprintCallable, Category = Trail)
	void StartTrail(TArray<UStaticMeshComponent*> InputSMCArrayRef, bool UseArray, UStaticMeshComponent* SMCReference, float TrailLifeTime, int MaxNumberOfSMCs, bool LengthTest, float vRef, float rRef);

	UFUNCTION(BlueprintCallable, Category = Trail)
	void FinishTrail();

	UFUNCTION(BlueprintCallable, Category = Trail)
	TArray<UStaticMeshComponent*> GetSMCArray();

	UFUNCTION(BlueprintCallable, Category = Trail)
	void ClearAllTrail();

	UFUNCTION(BlueprintCallable, Category = Trail)
		void RemoveSMC(UStaticMeshComponent* TrailSMCRef);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		FLinearColor StartColor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		FLinearColor EndColor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		FVector StartTrailScale;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		FVector EndTrailScale;

	UFUNCTION(BlueprintCallable, Category = Destroy)
	void OnDestroy();
	
protected:

	void CreateSMC();
	
	void TrailCicle();

	UStaticMeshComponent* LastSMC;

	UStaticMeshComponent* SMC;
	
	FTimerHandle SpawnTimer;

	FTimerHandle FinishTimer;

	TArray<UStaticMeshComponent*> SMCArray;

	float OldSpawnDelay;

	int MaxNumOfSMC;

	float MaxVL;

	float MaxRL;

	FVector LastLoc;

	FRotator LastRot;

	float GetRotLength(FRotator RotRef);

	bool IsLengthTest;

	bool UseArray;

	

	TArray<UStaticMeshComponent*> InputSMCArray;
};
