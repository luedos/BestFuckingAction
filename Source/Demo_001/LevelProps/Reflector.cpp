// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Engine.h"
#include "Projectails/Projectail.h"
#include "Reflector.h"


// Sets default values
AReflector::AReflector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ReflectorCollision"));
	BoxComponent->BodyInstance.bUseCCD = true;
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AReflector::OnComponentBeginOverlap);

	BoxComponent->bGenerateOverlapEvents = true;
	
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));

	Arrow->SetupAttachment(BoxComponent);

	SetActorEnableCollision(true);



}

// Called when the game starts or when spawned
void AReflector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReflector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AReflector::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Something!"));

	AProjectail* TestProj = Cast<AProjectail>(OtherActor);
	if (TestProj)
	{

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Some proj!"));
		FVector Velocity = TestProj->ProjectileMovement->Velocity;
		Velocity *= (-1);

		TestProj->ProjectileMovement->Velocity = FRotator(0, (Arrow->GetComponentRotation().Yaw * 2 - Velocity.Rotation().Yaw), 0).Vector()* Velocity.Size();
	}
}

