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


	HP = MaxHP;

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





UParticleSystemComponent * ASpawner::SpawnWithParticle(float ParticleTime, FVector LocationToSpawn)
{
	UParticleSystemComponent* LocalParticle = nullptr;

	UWorld* World = GetWorld();
	
	if (World != NULL)
	{
		if (SpawnParticle->IsValidLowLevel())
			LocalParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, LocationToSpawn, GetActorRotation());


		ParticleTimers.Add(FTimerHandle());
		TimerLocations.Add(LocationToSpawn);

		World->GetTimerManager().SetTimer(ParticleTimers.Last(), this, &ASpawner::SpawnByTimer, ParticleTime);

	}
	return LocalParticle;
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
			if (SpawnWithDelay)
				SpawnWithParticle(SpawnWithDelay, LocalPositions[i]);
			else {
				World->SpawnActor<AEnemy_Char>(EnemyToSpawn, LocalPositions[i], GetActorRotation(), SpawnParams);
				if (SpawnParticle->IsValidLowLevel())
					UParticleSystemComponent* TestParticle = UGameplayStatics::SpawnEmitterAtLocation(this, SpawnParticle, LocalPositions[i], GetActorRotation(), true);
			}
		}
	}
	AfterSpawn(LocalPositions.Num());
}

void ASpawner::DoDamage_Implementation(float Damage, ETeamEnum DamageFromTeam, AActor * Couser, EDamageType DamageType)
{
	if (IsSpawnerDamagable)
	{
		HP -= Damage;

		if (HP <= 0)
			DeathStatus();
	}
}

void ASpawner::AfterSpawn(int NumberOfSpawned)
{
}

void ASpawner::SpawnByTimer()
{
	UWorld* World = GetWorld();
	if (World != NULL)
		for (int i = 0; i < ParticleTimers.Num(); i++)
			if (!World->GetTimerManager().IsTimerActive(ParticleTimers[i]))
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Instigator = NULL;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				World->SpawnActor<AEnemy_Char>(EnemyToSpawn, LocalPositions[i], GetActorRotation(), SpawnParams);
				AfterSpawn(1);
				break;
			}
	

}

//void ASpawner::MyQueryFinished(TSharedPtr<FEnvQueryResult> Result)
//{
//	Result->GetAllAsLocations(LocalPositions);
//}

