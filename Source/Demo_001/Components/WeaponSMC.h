// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"

#include "WeaponSMC.generated.h"

/**
 * 
 */

enum class ESMCLookAt : uint8
{
	VE_AtChar 	UMETA(DisplayName = "LookAtChar"),
	VE_AtSceneComponent 	UMETA(DisplayName = "LookAtSceneComponent"),
	VE_AtRotation	UMETA(DisplayName = "LookAtRotation"),
	VE_SocketRotation UMETA(DisplayName = "UseSocketRotation")
};

UCLASS(Blueprintable,BlueprintType)
class DEMO_001_API UWeaponSMC : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UWeaponSMC();



	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Created)
	void OnCreated(ACharacter* CharRef, UStaticMesh* SMRef, UStaticMesh* SelfSM, UMaterial* SMMaterial);

	UFUNCTION(BlueprintCallable, Category = Rotation)
	void StartRotate(float RotRate, float StartRotInterpSpeedRef);

	UFUNCTION(BlueprintCallable, Category = Rotation)
		void AddRelativeRot();


	UFUNCTION(BlueprintNativeEvent)
	void AddRelativeRot_BNE();
	virtual void AddRelativeRot_BNE_Implementation();

	UFUNCTION(BlueprintCallable, Category = Rotation)
		void EndRotation(float EndRotInterpSpeedRef);

	UFUNCTION(BlueprintCallable, Category = Rotation)
	void SetRotationScale(float RotScale);

	UFUNCTION(BlueprintCallable, Category = Destroy)
	void OnDestroy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponSMCFearches)
	bool IsLookAtPoint;

	UFUNCTION(BlueprintCallable, Category = LookAt)
		void LookAtChar(ACharacter* Character);

	UFUNCTION(BlueprintCallable, Category = LookAt)
		void LookAtSceneComponent(USceneComponent* SceneComp);

	UFUNCTION(BlueprintCallable, Category = LookAt)
		void LookAtRotation(FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = LookAt)
		void LookBySocket();

	UFUNCTION(BlueprintCallable, Category = Meshes)
	TArray<UStaticMeshComponent*> GetComponentsArray();

protected:

	void LookAtPoint();

	FTimerHandle RotationTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponSMCFearches)
	float RotationRate;

	float OldRotationRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Char)
	ACharacter* Char;

	TArray<UStaticMeshComponent*> ComponentsArray;

	float InterpSpeed;

	float RotationScale;

	UStaticMesh* SM;
	
	UStaticMeshComponent* LastSMC;

	ESMCLookAt LookAtState;

	ACharacter* LookAtCharRef;

	USceneComponent* LookAtSceneComponentRef;

	FRotator LookAtRotatorRef;

};
