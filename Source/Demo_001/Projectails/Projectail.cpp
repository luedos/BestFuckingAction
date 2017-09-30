// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectails/DamageIntarface.h"
#include "Engine.h"
#include "Projectail.h"


// Sets default values
AProjectail::AProjectail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectailMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));

	RootComponent = ProjectailMesh;
	
	ProjectailMesh->BodyInstance.bUseCCD = true;

	ProjectailMesh->BodyInstance.SetCollisionProfileName("Projactile");


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = ProjectailMesh;
	ProjectileMovement->InitialSpeed = 2500.f;
	ProjectileMovement->MaxSpeed = 2500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0;

	bChangeParticleColor = false;

	bUseTeamVariable = false;

	bUseActorRotation = true;

	ProjectailTeam = ETeamEnum::TE_Neutral;
}

// Called when the game starts or when spawned
void AProjectail::BeginPlay()
{
	Super::BeginPlay();

	if (FollowParticle->IsValidLowLevel())
	{
		FollowParticleComponent = UGameplayStatics::SpawnEmitterAttached(FollowParticle, ProjectailMesh);

		FollowParticleComponent->BeginTrails("TrailSocket1", "TrailSocket2", ETrailWidthMode::ETrailWidthMode_FromCentre, 1);

		FollowParticleComponent->SetColorParameter("ParticleColor", ProjectailColor);
	}


}

// Called every frame
void AProjectail::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectail::DamageAfterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult, bool DestroyAfter)
{
	
		ETeamEnum SelfTeam = ETeamEnum::TE_Neutral;

		if (bUseTeamVariable)
		{
			SelfTeam = ProjectailTeam;
		}
		else
		{
			if (Char->IsValidLowLevel())
			{
				SelfTeam = Char->GetTeam();
			}
			else
			{
				SelfTeam = ProjectailTeam;
			}
		}



		if (OtherActor->IsValidLowLevel())
		{
			if (OtherActor->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
			{
				ACharPawn* TestCharPawn = Cast<ACharPawn>(OtherActor);
				if (TestCharPawn)
				{
					if (TestCharPawn->GetTeam() != SelfTeam)
					{
						if (OtherComp->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
						{
							IDamageIntarface::Execute_DoDamage(OtherComp, ProjectailDamage, NULL, Char, EDamageType::VE_Bullet);
							if(DestroyAfter)
								DestroyProjectailItself(SweepResult.Location);
						}

						else
						{
							IDamageIntarface::Execute_DoDamage(OtherActor, ProjectailDamage, NULL, Char, EDamageType::VE_Bullet);
							if (DestroyAfter)
								DestroyProjectailItself(SweepResult.Location);
						}

					}
				}

				else
				{
					if (OtherComp->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
					{
						IDamageIntarface::Execute_DoDamage(OtherComp, ProjectailDamage, NULL, Char, EDamageType::VE_Bullet);
						if (DestroyAfter)
							DestroyProjectailItself(SweepResult.Location);
					}
					else
					{
						IDamageIntarface::Execute_DoDamage(OtherActor, ProjectailDamage, NULL, Char, EDamageType::VE_Bullet);
						if (DestroyAfter)
							DestroyProjectailItself(SweepResult.Location);
					}

				}

			}
			else
			{
				if (OtherComp->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
				{
					IDamageIntarface::Execute_DoDamage(OtherComp, ProjectailDamage, NULL, Char, EDamageType::VE_Bullet);
					if (DestroyAfter)
						DestroyProjectailItself(SweepResult.Location);
				}

			}

		}

}

void AProjectail::DestroyProjectailItself(FVector SpawnParticlePoint)
{
	UWorld* World = GetWorld();
	
	if (World != NULL && DestroyParticle->IsValidLowLevel())
	{
		FRotator ParticleRotation;

		if (bUseActorRotation)
			ParticleRotation = GetActorRotation();
		else
			ParticleRotation = FRotator(0, 0, 0);

		 UParticleSystemComponent* TestParticle = UGameplayStatics::SpawnEmitterAtLocation(this, DestroyParticle, SpawnParticlePoint, ParticleRotation, true);

		 if (bChangeParticleColor)
		 {
			// UMaterialInstanceDynamic* TestMaterial = TestParticle->CreateDynamicMaterialInstance(0, TestParticle->GetMaterial(0));
			//
			// TestMaterial->SetVectorParameterValue(FName("Color"), ProjectailColor);
			//
			// if (TestParticle->GetMaterial(1)->IsValidLowLevel())
			// {
			//	 UMaterialInstanceDynamic* TestMaterial = TestParticle->CreateDynamicMaterialInstance(1, TestParticle->GetMaterial(1));
			//
			//	 TestMaterial->SetVectorParameterValue(FName("Color"), ProjectailColor);
			// }
			 TestParticle->SetColorParameter("ParticleColor", ProjectailColor);
		 }


	}

	if(FollowParticle->IsValidLowLevel())
		FollowParticleComponent->SetActive(false);

	ProjectailMesh->SetVisibility(false);
	ProjectailMesh->BodyInstance.SetCollisionProfileName("IgnorAll");
	ProjectileMovement->Velocity = FVector(0, 0, 0);
	ProjectileMovement->InitialSpeed = 0.f;

	if(ProjDestroySound->IsValidLowLevel())
	UGameplayStatics::SpawnSoundAtLocation(this, ProjDestroySound, GetActorLocation());

	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AProjectail::DestroyFunction, DestroyDelay, false);
	
}
