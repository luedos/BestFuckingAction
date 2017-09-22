// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Spawner.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->InitCapsuleSize(70, 120);
	CapsuleComponent->BodyInstance.SetCollisionProfileName("Pawn");

	RootComponent = CapsuleComponent;

	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));

	SpawnerMesh->BodyInstance.SetCollisionProfileName("PawnMesh");

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	//*MyQueryRequest = FEnvQueryRequest(MyQuery, this);

	//MyQueryRequest->SetFloatParam("CircleRadiusParam", SpawnRadius);
	
}

// Called every frame
void ASpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASpawner::Spawn()
{
	ExecuteSpawn();
}





void ASpawner::ExecuteSpawn()
{
	

	UWorld* World = GetWorld();

	LocalPositions.Empty();

	switch (SpawnerType)
	{
	case ESpawnType::ArrayPoints:
	{
		

		for (int i = 0; i < Positions.Num(); i++)
			LocalPositions.Add(Positions[i] + GetActorLocation());
	}
		break;
	case ESpawnType::EQS:
		break;
	case ESpawnType::RandomInSphere:
		break;
	default:
		break;
	}
			
	
	//else
	//{
	//	TArray<FVector> LocalArray;
	//
	//	MyQueryRequest->Execute(EEnvQueryRunMode::RandomBest5Pct, this, &ASpawner::MyQueryFinished);
	//	for (int i = 0; i < 3; i++)
	//	{
	//		int LocalInt = FMath::RandRange(0, float(LocalPositions.Num()) - 0.1);
	//
	//		LocalArray.Add(LocalPositions[LocalInt]);
	//
	//		LocalPositions.RemoveAt(i);
	//	}
	//
	//	LocalPositions = LocalArray;
	//}
	if(SpawnerSpawnParticle->IsValidLowLevel())
		UParticleSystemComponent* TestSpawnParticle = UGameplayStatics::SpawnEmitterAtLocation(this, SpawnerSpawnParticle, GetActorLocation(), GetActorRotation(), true);

	if (World != NULL)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = NULL;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		for (int i = 0; i < LocalPositions.Num(); i++)
		{
			World->SpawnActor<AEnemy_Char>(EnemyToSpawn, LocalPositions[i], GetActorRotation(), SpawnParams);
			if (EnemySpawnParticle->IsValidLowLevel())
				UParticleSystemComponent* TestParticle = UGameplayStatics::SpawnEmitterAtLocation(this, EnemySpawnParticle, LocalPositions[i], GetActorRotation(), true);
		}
	}
	AfterSpawn(LocalPositions.Num());
}

void ASpawner::AfterSpawn(int NumberOfSpawned)
{
}

//void ASpawner::MyQueryFinished(TSharedPtr<FEnvQueryResult> Result)
//{
//	Result->GetAllAsLocations(LocalPositions);
//}

