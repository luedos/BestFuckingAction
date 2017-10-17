// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Objects/Weapons/MC_Weapon.h"
#include "MC_LaserBeam.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API UMC_LaserBeam : public UMC_Weapon
{
	GENERATED_BODY()


	virtual bool OnCreated(ACharPawn* CharRef) override;
	
	virtual bool FirstFire(APlayerController* InstigatorFF, FVector PointToShootFF, FRotator RotToShootFF) override;

	virtual bool SecondFire(APlayerController* InstigatorSF, FVector PointToShootSF, FRotator RotToShootSF) override;
	
public:

	UMC_LaserBeam();

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Particle)
	void SpawnParticle_BNE(FVector Start, FVector End, bool bSpawnHitParticle);
	virtual void SpawnParticle_BNE_Implementation(FVector Start, FVector End, bool bSpawnHitParticle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LaserStats)
	float FireRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LaserStats)
	float RicochetRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LaserStats)
	float RicochetAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LaserStats)
	int NumOfRicochtCheck;
	
private:

	void Ricochet(APlayerController* FireInstigator, FVector Normal, FVector Point, FVector ActorPos, float Angle, int NumOfChecks);

	int BeamFire(UObject*& ObjectRef, FVector& ShotedPoint, FVector Start, FVector End, ECollisionChannel PrefferedChannel);

	UObject* DesiredObject;

};
