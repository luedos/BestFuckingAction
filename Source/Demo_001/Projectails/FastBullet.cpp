// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FastBullet.h"


// Sets default values
AFastBullet::AFastBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));

	RootComponent = BulletMesh;
	BulletMesh->SetWorldScale3D(FVector(0.5f, 0.07f, 0.07f));
	BulletMesh->BodyInstance.bUseCCD = true;



	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = BulletMesh;
	ProjectileMovement->InitialSpeed = 2500.f;
	ProjectileMovement->MaxSpeed = 2500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0;



	bUseTeamVariable = false;
}

// Called when the game starts or when spawned
void AFastBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFastBullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

