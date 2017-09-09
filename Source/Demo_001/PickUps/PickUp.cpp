// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "PickUp.h"


// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(200);
	RootComponent = CollisionComp;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	PickUpMesh->AttachTo(CollisionComp);

}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUp::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APickUp::PickUp(AActor * ActorWhichPickUp)
{

}

bool APickUp::GetCanPickUp()
{
	return CanPickUp;
}

void APickUp::SetCanPickUp(bool NewPickUpState)
{
	CanPickUp = NewPickUpState;
}

