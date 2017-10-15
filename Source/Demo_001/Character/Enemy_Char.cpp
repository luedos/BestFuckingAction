// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy_Char.h"


// Sets default values
AEnemy_Char::AEnemy_Char()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FaceArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FaceArrowComponent"));
	FaceArrow->SetupAttachment(RootComponent);

	Team = ETeamEnum::TE_Enemy;

	IsInDelay = false;
}

// Called when the game starts or when spawned
void AEnemy_Char::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Char::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}



void AEnemy_Char::StartEnemyDelay(float InDelay)
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		if (World->GetTimerManager().IsTimerActive(EnemyDelayTimer))
			World->GetTimerManager().ClearTimer(EnemyDelayTimer);

		IsInDelay = true;

		World->GetTimerManager().SetTimer(EnemyDelayTimer, this, &AEnemy_Char::StopEnemyDelay, InDelay);
	}

}

void AEnemy_Char::StopEnemyDelay()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
		if (World->GetTimerManager().IsTimerActive(EnemyDelayTimer))
			World->GetTimerManager().ClearTimer(EnemyDelayTimer);

	IsInDelay = false;
}



void AEnemy_Char::EnemyFire_Implementation(int NumberOfFire, AActor* Target, bool ShootWhileVisible)
{}

bool AEnemy_Char::InterpFaceArrow(float TimeDelay, FVector ToPoint)
{
	
	if(InterpOrRot)
		FaceArrow->SetWorldRotation(UKismetMathLibrary::RInterpTo(
			FRotator(0, FaceArrow->GetComponentRotation().Yaw, 0),
			FRotator(0, UKismetMathLibrary::FindLookAtRotation(FaceArrow->GetComponentLocation(), ToPoint).Yaw, 0),
			TimeDelay, ArrowInterpSpeed));
	else
	{
		FRotator Target = UKismetMathLibrary::FindLookAtRotation(FaceArrow->GetComponentLocation(), ToPoint);

		if (UKismetMathLibrary::Abs(FaceArrow->GetComponentRotation().Yaw - Target.Yaw) < TimeDelay * ArrowRotSpeed)
			FaceArrow->SetWorldRotation(Target);
		else
		{
			FRotator Point = FaceArrow->GetComponentRotation();


			if (Point.Yaw < 0)
				Point.Yaw += 360;
			
			if (Target.Yaw < 0)
				Target.Yaw += 360;

			if(UKismetMathLibrary::Abs(Target.Yaw - Point.Yaw) > 180)
				Point.Yaw -= ((Target.Yaw - Point.Yaw) / UKismetMathLibrary::Abs(Target.Yaw - Point.Yaw)) * TimeDelay * ArrowRotSpeed;
			else
				Point.Yaw += ((Target.Yaw - Point.Yaw) / UKismetMathLibrary::Abs(Target.Yaw - Point.Yaw)) * TimeDelay * ArrowRotSpeed;

			FaceArrow->SetWorldRotation(Point);
		}


	}

	



	return true;
}


