// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/CharPawn.h"
#include "Enemy_Char.generated.h"

UCLASS()
class DEMO_001_API AEnemy_Char : public ACharPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Char();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UFUNCTION(BlueprintCallable, Category = EnemyDelay)
	void StartEnemyDelay(float InDelay);

	UFUNCTION(BlueprintCallable, Category = EnemyDelay)
	void StopEnemyDelay();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Fire)
	void EnemyFire(int NumberOfFire, AActor* Target, bool ShootWhileVisible);
	virtual void EnemyFire_Implementation(int NumberOfFire, AActor* Target, bool ShootWhileVisible);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Color)
	FLinearColor HitParticleColor;

protected:

	FTimerHandle EnemyDelayTimer;


	UPROPERTY(BlueprintReadOnly, Category = EnemyDelay)
	bool IsInDelay;

	
};
