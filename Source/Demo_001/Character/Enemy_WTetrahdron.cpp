// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy_WTetrahdron.h"

AEnemy_WTetrahdron::AEnemy_WTetrahdron()
{
		DeshLength = 800.f;
		DeshTime = 0.15f;
		NumberOfSmallDeshes = 40;
		CountOfSmallDeshes = 0;

		ASinConst = 15.f;
		BSinConst = 15.f;
		SinHight = 1000.f;
		StartDeshSpeed = 100.f;
		ArraySum = 0;
		Coefficient = 0;
}




void AEnemy_WTetrahdron::StartDesh(FVector PointToDeshRef)
{
	UWorld* World = GetWorld();
	if (World != NULL)
	{

		if (!World->GetTimerManager().IsTimerActive(DeshTimer))
		{
			LengthsArray.Empty();
			ArraySum = 0;
			for (int i = 0; i < NumberOfSmallDeshes; i++)
			{
				float li;
				li = StartDeshSpeed * NumberOfSmallDeshes / DeshTime;
				li += (SinHight * NumberOfSmallDeshes / DeshTime) * UKismetMathLibrary::Sin((ASinConst + (UKismetMathLibrary::Conv_IntToFloat(i) / UKismetMathLibrary::Conv_IntToFloat(NumberOfSmallDeshes)) * (180.f - ASinConst - BSinConst)) * 3.14159f / 180.f);

					

				ArraySum += li;

				LengthsArray.Add(li);
			}
	

			Coefficient = DeshLength / ArraySum;

			CountOfSmallDeshes = 0;
			PointToDesh = PointToDeshRef;
			World->GetTimerManager().SetTimer(DeshTimer, this, &AEnemy_WTetrahdron::DeshCicle, DeshTime / NumberOfSmallDeshes, true, DeshTime / NumberOfSmallDeshes);

			StartDeshBNE(PointToDeshRef);

			TestFunction();
		}
	}
	
}

void AEnemy_WTetrahdron::DeshCicle()
{
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		
		FVector DeshVector;

		DeshVector = (PointToDesh - GetActorLocation()) / (PointToDesh - GetActorLocation()).Size();



		FVector Start = GetActorLocation();
		FVector End = Start + DeshVector * 50.f;

		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, this);
		TraceParams.bTraceComplex = true;
		TraceParams.AddIgnoredActor(this);
		FHitResult HitOut;
		ECollisionChannel CollisionChannel = ECC_Pawn;

		if (CountOfSmallDeshes >= LengthsArray.Num() || (PointToDesh - GetActorLocation()).Size() < 50.f)
		{
			StopDesh();
		}

		else
		{

			if (World->LineTraceSingleByChannel(HitOut, Start, End, CollisionChannel, TraceParams))
			{
				StopDesh();
			}
			else
			{
				SetActorLocation(GetActorLocation() + DeshVector * LengthsArray[CountOfSmallDeshes] * Coefficient);
				CountOfSmallDeshes++;
			}
		}
		
		

	

	}
}

void AEnemy_WTetrahdron::StopDesh()
{
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		World->GetTimerManager().ClearTimer(DeshTimer);
		StopDeshBNE();
	}
}

void AEnemy_WTetrahdron::TestFunction_Implementation()
{
}

void AEnemy_WTetrahdron::StartDeshBNE_Implementation(FVector PointDeshRef)
{
}

void AEnemy_WTetrahdron::StopDeshBNE_Implementation()
{
}
