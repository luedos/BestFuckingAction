// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Trail20.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO_001_API UTrail20 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrail20();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		float TrailTimeLength;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		int NumOfTrailMeshes;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		int MaxNumOfBackSMC;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Trail)
		UMaterial* TrailMaterial;

	UFUNCTION(BlueprintCallable, Category = Trail)
		void StartTrail(float TrailLength, UStaticMeshComponent* SMCReference);

	UFUNCTION(BlueprintCallable, Category = Trail)
		void ClearAllTrail();

	UFUNCTION(BlueprintCallable, Category = Trail)
		TArray<UStaticMeshComponent*> GetMeshArray();

	UFUNCTION(BlueprintCallable, Category = Trail)
		TArray<UStaticMeshComponent*> GetBackMeshArray();

	UFUNCTION(BlueprintCallable, Category = Trail)
		TArray<float> GetDelayArray();

	UFUNCTION(BlueprintCallable, Category = Trail)
		void FinishTrail();

	UFUNCTION(BlueprintCallable, Category = Trail)
		int TestFunction(UStaticMeshComponent* SMCTestReference);

protected:

	UStaticMeshComponent* SMC;

	UStaticMeshComponent* LastSMC;

	float DeleteDelay;

	int MinNumOfBackSMC;

	TArray<UStaticMeshComponent*> SMCsArray;

	TArray<UStaticMeshComponent*> BackSMCsArray;

	TArray<float> DeleteDelayArray;

	FTimerHandle TrailTimer;

	FTimerHandle FinishTrailTimer;

	FTimerHandle DestroyTimer;

	FTimerHandle CreateSMCTimer;

	void TransferSMC();

	void CreateMeshComponent();

	void DestroyMeshComponent();

	void TrailCicle();

	void DeleteCicle();
	
};
