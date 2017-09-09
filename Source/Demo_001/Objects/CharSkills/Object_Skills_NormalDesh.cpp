// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Engine.h"
#include "Object_Skills_NormalDesh.h"

void UObject_Skills_NormalDesh::UseSkill_Implementation(ACharacter * Char, float FloatA, float FloatB, FVector Vector)
{
	Desh(Char, FloatA, FloatB, Vector);
}

void UObject_Skills_NormalDesh::Desh(ACharacter * Char, float SpeedOfDesh, float Distance, FVector Direction)
{

	if (Char->IsValidLowLevel())
	{
		
		UWorld* World = Char->GetWorld();
		if (World != NULL)
		{

			if (!World->GetTimerManager().IsTimerActive(TimerOfDesh) && Direction != FVector(0,0,0))
			{


				CharToDesh = Char;
				MySpeedOfDesh = SpeedOfDesh;
				MyDistanse = Distance;
				NumberOfJumps = 0;
				RotToDesh = FRotator(0.f, Direction.Rotation().Yaw, 0.f);
				float TimerDelay = MyDistanse / (MySpeedOfDesh*80.f);
				World->GetTimerManager().SetTimer(TimerOfDesh, this, &UObject_Skills_NormalDesh::DeshInProcess, TimerDelay, true, TimerDelay);



			}
		}
	}
}

void UObject_Skills_NormalDesh::DeshInProcess()
{
	if (CharToDesh->IsValidLowLevel())
	{
		UWorld* World = CharToDesh->GetWorld();
		if (NumberOfJumps <= 80)
		{
			FVector Start = CharToDesh->GetActorLocation();
			FVector End = Start + RotToDesh.Vector()*60.f;

			FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, CharToDesh);
			TraceParams.bTraceComplex = true;
			TraceParams.AddIgnoredActor(CharToDesh);
			FHitResult HitOut;
			ECollisionChannel CollisionChannel = ECC_Pawn;

			if (World->LineTraceSingleByChannel(HitOut, Start, End, CollisionChannel, TraceParams))
			{
				World->GetTimerManager().ClearTimer(TimerOfDesh);
			}

			else
			{
				CharToDesh->SetActorLocation(Start + RotToDesh.Vector()*MyDistanse / 80.f);
				NumberOfJumps++;
			}
		}
		else
		{
			World->GetTimerManager().ClearTimer(TimerOfDesh);
		}
	}
}


