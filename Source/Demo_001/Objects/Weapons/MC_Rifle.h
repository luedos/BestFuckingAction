// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Objects/Weapons/MC_Weapon.h"
#include "Projectails/Projectail.h"
#include "MC_Rifle.generated.h"

/**
 * 
 */


UCLASS()
class DEMO_001_API UMC_Rifle : public UMC_Weapon
{
	GENERATED_BODY()
	
		virtual bool FirstFire(APlayerController* InstigatorFF, FVector PointToShootFF, FRotator RotToShootFF) override;
	
		virtual bool SecondFire(APlayerController* InstigatorSF, FVector PointToShootSF, FRotator RotToShootSF) override;


		virtual bool OnCreated(ACharPawn* CharRef) override;

public:

	UMC_Rifle();
	
protected:

	UPROPERTY(EditAnywhere, Category = Fire)
	class TSubclassOf<AProjectail> BulletToShoot;

	UPROPERTY(EditAnywhere, Category = Fire)
	float Angle;

	UPROPERTY(EditAnywhere, Category = Fire)
	float StartAngle;

	UPROPERTY(EditAnywhere, Category = Fire)
	int NumOfShots;

	UPROPERTY(EditAnywhere, Category = Fire)
		float ShotLength;

	UPROPERTY(EditAnywhere, Category = Fire)
		float SFDamage;

	UPROPERTY(EditAnywhere, Category = Fire)
	bool bShowShotGunRays;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visualisation)
	UParticleSystem* DamageParticleSF;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visualisation)
		UParticleSystem* ShotGunRayParticle;

private:

	UObject* MultiTrace(FVector StartPointToShoot, FVector EndPointToShoot, ECollisionChannel PrefferedChannel);


};

