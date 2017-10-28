// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Character/Enemy_Char.h"
#include "Projectails/DamageIntarface.h"
#include "Spawner.generated.h"



UENUM(BlueprintType)
enum class ESpawnType : uint8
{
	ArrayPoints 	UMETA(DisplayName = "ArrayPoints"),
	EQS		UMETA(DisplayName = "EQS system"),
	RandomInSphere	UMETA(DisplayName = "Random In Sphere")
};

UCLASS()
class DEMO_001_API ASpawner : public AActor, public IDamageIntarface
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, Category = SpawnerMesh)
		class UStaticMeshComponent* SpawnerMesh;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LedgeGrab, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComponent;
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Spawn)
	virtual void Spawn();

	UPROPERTY(EditAnywhere, Category = Spawn)
	TSubclassOf<AEnemy_Char> EnemyToSpawn;

	UPROPERTY(EditAnywhere, Category = Spawn)
	float SpawnDelay = 0.5;
	UPROPERTY(EditAnywhere, Category = Spawn)
	bool SpawnWithDelay = false;

	UParticleSystemComponent* SpawnWithParticle(float ParticleTime, FVector LocationToSpawn);

	void ExecuteSpawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawn)
	int HowMuchToSpawn = 0;

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (MakeEditWidget = true))
	TArray<FVector> Positions;
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawn)
	//UEnvQuery* MyQuery; 
	
	//FEnvQueryRequest* MyQueryRequest;
	
	//void MyQueryFinished(TSharedPtr<FEnvQueryResult> Result);

	UPROPERTY(EditAnywhere, Category = Spawn)
	ESpawnType SpawnerType = ESpawnType::ArrayPoints;

	UPROPERTY(EditAnywhere, Category = Spawn)
	float SpawnRadius;

	UPROPERTY(EditAnywhere, Category = Spawn)
	ETeamEnum MyTeam = ETeamEnum::TE_Enemy;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Damage)
		void DoDamage(float Damage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType);
	virtual void DoDamage_Implementation(float Damage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = HP)
	void DeathStatus();

	bool IsSpawnerDamagable = false;

protected:

	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* SpawnParticle;

	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* SpawnerSpawnParticle;

	virtual void AfterSpawn(int NumberOfSpawned);

	UPROPERTY(EditAnywhere, Category = Spawner)
	float MaxHP = 150;

	float HP;

private:

	void SpawnByTimer();

	TArray<FVector> TimerLocations;

	TArray<FTimerHandle> ParticleTimers;

	TArray<FVector> LocalPositions;
};
