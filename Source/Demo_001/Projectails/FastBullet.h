// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Character/CharPawn.h"
#include "FastBullet.generated.h"

UCLASS()
class DEMO_001_API AFastBullet : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	class UStaticMeshComponent* BulletMesh;
	
public:	
	// Sets default values for this actor's properties
	AFastBullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	


	APlayerController* Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "TeamVar", ExposeOnSpawn = true), Category = Team)
	ETeamEnum ProjectailTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "UseTeamVar", ExposeOnSpawn = true), Category = Team)
	bool bUseTeamVariable;
};
