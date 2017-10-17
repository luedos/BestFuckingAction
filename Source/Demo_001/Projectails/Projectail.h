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
	
public:


		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
		class UStaticMeshComponent* ProjectailMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Reflector)
		USphereComponent* SphereComponent;

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectail)
	bool DestroyAfterOverlap = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectail)
	bool OverrideOverlapSphere = false;

	UFUNCTION(BlueprintCallable, Category = Projectail)
	bool DamageAfterOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult &SweepResult, bool DestroyAfter);

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DestroyParticle)
	FColor ProjectailColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DestroyParticle)
	bool bChangeParticleColor;

	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* FollowParticle;
	
	UPROPERTY(EditAnywhere, Category = Visualisation)
	USoundBase* ProjDestroySound;

	UParticleSystemComponent* FollowParticleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DestroyParticle)
	bool bUseActorRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectail)
	float ProjectailDamage;

	UFUNCTION(BlueprintCallable, Category = Projectail)
	void DestroyProjectailItself(FVector SpawnParticlePoint);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DestroyParticle)
	UParticleSystem* DestroyParticle;

	UPROPERTY(EditAnywhere, Category = FollowParticle)
	float DestroyDelay = 0.5f;

	FTimerHandle DestroyTimer;

	void DestroyFunction() { Destroy(); }

};
