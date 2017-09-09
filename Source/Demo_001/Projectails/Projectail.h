// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Character/CharPawn.h"
#include "ParticleDefinitions.h"

#include "Projectail.generated.h"


UCLASS()
class DEMO_001_API AProjectail : public AActor
{
	GENERATED_BODY()
	
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
		class UStaticMeshComponent* ProjectailMesh;

public:	
	// Sets default values for this actor's properties
	AProjectail();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "TeamVar", ExposeOnSpawn = true), Category = Team)
	ACharPawn* Char;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "TeamVar", ExposeOnSpawn = true), Category = Team)
	ETeamEnum ProjectailTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "UseTeamVar", ExposeOnSpawn = true), Category = Team)
	bool bUseTeamVariable;
	
	UFUNCTION(BlueprintCallable, Category = Projectail)
	void DamageAfterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult,  bool DestroyAfter = true);


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DestroyParticle)
	FColor ProjectailColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DestroyParticle)
	bool bChangeParticleColor;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	//bool bCreateParticleActor;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	//float DelayInDestroyParticle;
	//
	//UPROPERTY(EditAnywhere, Category = Particle)
	//UParticleSystem* FollowParticle;
	//
	//UPROPERTY(EditAnywhere, Category = Particle)
	//TSubclassOf<AProjParticleHolder> ParticleHolderClass;
	//
	//UPROPERTY(EditAnywhere, Category = Particle)
	//FVector ScaleParticleHolder = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DestroyParticle)
	bool bUseActorRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectail)
	float ProjectailDamage;

	UFUNCTION(BlueprintCallable, Category = Projectail)
	void DestroyProjectailItself(FVector SpawnParticlePoint);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DestroyParticle)
	UParticleSystem* DestroyParticle;


	//AProjParticleHolder* MyParticleHolder;

};
