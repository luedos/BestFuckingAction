// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class DEMO_001_API APickUp : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	class UStaticMeshComponent* PickUpMesh;
	
public:	
	// Sets default values for this actor's properties
	APickUp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PickUp(AActor* ActorWhichPickUp);
	
	UFUNCTION(BlueprintPure, Category = PickUp)
	bool GetCanPickUp();
	UFUNCTION(BlueprintCallable, Category = PickUp)
	void SetCanPickUp(bool NewPickUpState);

private:

	bool CanPickUp;

};
