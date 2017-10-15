// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "CharPawn.h"


// Sets default values
ACharPawn::ACharPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HP = MaxHP;

	IsDead = false;

	bCanCharBeDamaged = true;
}

// Called when the game starts or when spawned
void ACharPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACharPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

ETeamEnum ACharPawn::GetTeam()
{
	return Team;
}

bool ACharPawn::TestForVisibilityOnActor(AActor* TestActor)
{
	bool IsSucsess = false;

	if (TestActor->IsValidLowLevel())
	{
		UWorld* World = GetWorld();
		if (World != NULL)
		{
			


			TArray<FHitResult> HitOut;

			FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, this);

			World->LineTraceMultiByChannel(HitOut, GetActorLocation(), TestActor->GetActorLocation(), ECC_GameTraceChannel5, TraceParams);

			if (HitOut.Num() != 0)
			{
				for (int i = 0; i < HitOut.Num(); i++)
				{
					if (HitOut[i].GetActor()->IsValidLowLevel())
					{
						if (HitOut[i].GetActor() != TestActor)
						{
							ACharPawn* TestChar = Cast<ACharPawn>(HitOut[i].GetActor());
							if (TestChar)
							{
								if (TestChar->GetTeam() != GetTeam())
								{
									IsSucsess = false;
									break;
								}
							}
							else
							{
								IsSucsess = false;
								break;
							}
						}
						else
						{
							IsSucsess = true;
							break;
						}
					}
					else
					{
						if (HitOut[i].bBlockingHit)
						{
							IsSucsess = false;
							break;
						}
					}
					
				}
			}
			
		}
	}

	return IsSucsess;

}

bool ACharPawn::GetIsDead()
{
	return IsDead;
}

void ACharPawn::DoDamage_Implementation(float Damage, APlayerController* CallInstigator, AActor* Couser, EDamageType DamageType)
{

}

void ACharPawn::DamageHP(float Damage)
{
	if (bCanCharBeDamaged)
	{
		HP = HP - Damage;
		if (HP > MaxHP)
		{
			HP = MaxHP;
		}
		if (HP < 0)
		{
			IsDead = true;
			DeathStatus();
		}
	}
}

void ACharPawn::SetCanCharBeDamaged(bool NewStatus)
{
	bCanCharBeDamaged = NewStatus;
}