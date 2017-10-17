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

		ArrowInterpSpeed = 5;

		ArrowRotSpeed = 360;

		RayRotSpeed = 30;
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




void AEnemy_WTetrahdron::StopRayCicle()
{
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		InterpOrRot = true;
		ArrowRotSpeed = LocalRotationRate;
		World->GetTimerManager().ClearTimer(RayTimer);
		World->GetTimerManager().SetTimer(RayTimer, this, &AEnemy_WTetrahdron::SetTrueCanRay, SetCanRayTrueLength, false, SetCanRayTrueLength);
		RayParticleComponent->DestroyComponent();
		if (ArcParticle->IsValidLowLevel())
			ArcParticle->DestroyComponent();

		SetCanCharBeDamaged(true);

		StopRayBNE();
	}
}

void AEnemy_WTetrahdron::StartRayCicle(float RayLengthRef)
{


	UWorld* World = GetWorld();
	if (World != NULL)
	{
		RayTime = 0;
		RayTimeLength = RayLengthRef;
		InterpOrRot = false;
		LocalRotationRate = ArrowRotSpeed;
		ArrowRotSpeed = RayRotSpeed;
		World->GetTimerManager().SetTimer(RayTimer, this, &AEnemy_WTetrahdron::RayCicle, 0.005f, true);

		if (RayParticle->IsValidLowLevel())
		{
			RayParticleComponent = UGameplayStatics::SpawnEmitterAttached(RayParticle, GetMesh());
			RayParticleComponent->SetBeamSourcePoint(0, GetActorLocation(), 0);
			RayParticleComponent->SetColorParameter("ParticleColor", CharColor);
		}
	}
}

void AEnemy_WTetrahdron::RayCicle()
{
	TArray<FHitResult> HitOut;

	TArray<AActor*> ActorToIgnor;

	UKismetSystemLibrary::SphereTraceMulti_NEW(this, GetActorLocation() + FaceArrow->GetComponentRotation().Vector() * 50,
		GetActorLocation() + FaceArrow->GetComponentRotation().Vector() * RayLength, 25,
		ETraceTypeQuery::TraceTypeQuery3, true, ActorToIgnor, EDrawDebugTrace::None, HitOut, true);

	if (RayParticleComponent->IsValidLowLevel())
		RayParticleComponent->SetBeamTargetPoint(0, GetActorLocation() + FaceArrow->GetComponentRotation().Vector() * RayLength, 0);

	if (HitOut.Num() != 0)
	{
		for (int i = 0; i < HitOut.Num(); i++)
		{
			if (HitOut[i].GetActor()->IsValidLowLevel())
			{
				if (HitOut[i].GetActor()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
				{
					ACharPawn* TestCharPawn = Cast<ACharPawn>(HitOut[i].GetActor());
					if (TestCharPawn)
					{
						if (TestCharPawn->GetTeam() != GetTeam())
						{
							if (HitOut[i].GetComponent()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
							{
								//Тест на компонент
								IDamageIntarface::Execute_DoDamage(HitOut[i].GetComponent(), RayDamageRate * 0.005f, GetTeam(), this, EDamageType::VE_LaserBeam);
								if (RayParticleComponent->IsValidLowLevel())
									RayParticleComponent->SetBeamTargetPoint(0, HitOut[i].ImpactPoint, 0);
								break;
							}

							else
							{
								IDamageIntarface::Execute_DoDamage(HitOut[i].GetActor(), RayDamageRate * 0.005f, GetTeam(), this, EDamageType::VE_LaserBeam);
								if (RayParticleComponent->IsValidLowLevel())
									RayParticleComponent->SetBeamTargetPoint(0, HitOut[i].ImpactPoint, 0);
								break;
							}

						}
					}

					else
					{
						if (HitOut[i].GetComponent()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
						{
							IDamageIntarface::Execute_DoDamage(HitOut[i].GetComponent(), RayDamageRate * 0.005f, GetTeam(), this, EDamageType::VE_LaserBeam);
							if (RayParticleComponent->IsValidLowLevel())
								RayParticleComponent->SetBeamTargetPoint(0, HitOut[i].ImpactPoint, 0);
							break;
						}
						else
						{
							IDamageIntarface::Execute_DoDamage(HitOut[i].GetActor(), RayDamageRate * 0.005f, GetTeam(), this, EDamageType::VE_LaserBeam);
							if (RayParticleComponent->IsValidLowLevel())
								RayParticleComponent->SetBeamTargetPoint(0, HitOut[i].ImpactPoint, 0);
							break;
						}

					}

				}
				else
				{
					if (HitOut[i].GetComponent()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
					{
						//Тест на компонент
						IDamageIntarface::Execute_DoDamage(HitOut[i].GetComponent(), RayDamageRate * 0.005f, GetTeam(), this, EDamageType::VE_LaserBeam);
						if (RayParticleComponent->IsValidLowLevel())
							RayParticleComponent->SetBeamTargetPoint(0, HitOut[i].ImpactPoint, 0);
						break;
					}
					else
					{
						if (HitOut[i].bBlockingHit)
						{
							break;
						}
					}
				}
			}
			else
			{
				if (HitOut[i].bBlockingHit)
				{
					if (RayParticleComponent->IsValidLowLevel())
						RayParticleComponent->SetBeamTargetPoint(0, HitOut[i].ImpactPoint, 0);
					break;
				}
			}
		}




	}

	RayTime += 0.005f;

	if (RayTime > RayTimeLength)
		StopRayCicle();
}
