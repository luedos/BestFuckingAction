// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"

#include "Projectails/FastBullet.h"
#include "Projectails/DamageIntarface.h"
#include "Components/WeaponSMC.h"
#include "Components/Shield.h"
#include "Components/Trail30.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "MC_Rifle.h"


struct ActorGroup
{
	AActor* Actor;
	int NumOfShots;
};

UMC_Rifle::UMC_Rifle()
{
	Angle = 40.f;

	StartAngle = 60.f;

	NumOfShots = 10;

	ShotLength = 1000.f;

	SFDamage = 51.f;

	bShowShotGunRays = false;
}

bool UMC_Rifle::OnCreated(ACharPawn* CharRef)
{
	
		if (CharRef->IsValidLowLevel())
		{
			Char = CharRef;


			if (IsSMC)
			{
				SMC = NewObject<UWeaponSMC>(Char, WeaponSMCRef);
				SMC->OnComponentCreated();
				SMC->RegisterComponent();

				SMC->SetStaticMesh(ShapeMesh);
				SMC->OnCreated(Char, GunMesh, ShapeMesh, MeshMat);
				SMC->LookAtChar(Char);
				SMC->IsLookAtPoint = true;
				SMC->StartRotate(270.f, 10);
			}
				OnCreated_BNE();
			
			//TrailComponent = NewObject<UTrail30>(Char);
			//TrailComponent->OnComponentCreated();
			//TrailComponent->RegisterComponent();

			//TrailComponent->SpawnDelay = 0.2;
			//TrailComponent->TrailMaterial = TrailMat;
			//TrailComponent->TrailTimeLength = 0.4f;

			//TrailComponent->StartTrailScale = FVector(1.2f, 1.2f, 1.2f);
			//TrailComponent->EndTrailScale = FVector(0.2f, 0.2f, 0.2f);


			//TrailComponent->StartColor = StartTrailColor;
			//TrailComponent->EndColor = EndTrailColor;


			//TrailComponent->StartTrail(SMC->GetComponentsArray(), true, SMC, 0.f, 30, false, 0.f, 0.f);

			return true;
		}
		else
		{
			return false;
		}
	
}

bool UMC_Rifle::FirstFire(APlayerController* InstigatorFF, FVector PointToShootFF, FRotator RotToShootFF)
{
	if (Char->IsValidLowLevel())
	{
		if (Ammo > 0)
		{
			UWorld* World = Char->GetWorld();
			if (World != NULL)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Instigator = InstigatorFF->GetCharacter();
				SpawnParams.Owner = InstigatorFF->GetCharacter();


				AProjectail* ShotedBullet = World->SpawnActorDeferred<AProjectail>(BulletToShoot, FTransform(RotToShootFF, PointToShootFF, FVector(1.f, 1.f, 1.f)), Char, InstigatorFF->GetCharacter(),  ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

				if (ShotedBullet)
				{
					ShotedBullet->bUseTeamVariable = true;

					ShotedBullet->ProjectailTeam = ETeamEnum::TE_Player;

					UGameplayStatics::FinishSpawningActor(ShotedBullet, FTransform(RotToShootFF,  PointToShootFF));


				}

				if (FireParticleFF->IsValidLowLevel())
				{
					UGameplayStatics::SpawnEmitterAtLocation(Char, FireParticleFF, PointToShootFF, RotToShootFF);
				}


				Ammo -= 1;
				return true;
			}
			else 
			{

				return false;
			}
		}

		else
		{

			return false;
		}
	}
	else
	{

		return false;
	}
}

bool UMC_Rifle::SecondFire(APlayerController* InstigatorSF, FVector PointToShootSF, FRotator RotToShootSF)
{
	if (Char->IsValidLowLevel())
	{
		if (Ammo > 4)
		{
			UWorld* World = InstigatorSF->GetCharacter()->GetWorld();
			if (World != NULL)
			{
				TArray<UObject*> ActorArray;


				FHitResult HitOut;
				
				FVector FirstPoint = PointToShootSF - RotToShootSF.Vector() * 100.f;

				FRotator StartRotator = FRotator(RotToShootSF.Pitch, RotToShootSF.Yaw - Angle / 2.f, RotToShootSF.Roll);

				for (int i = 0; i < NumOfShots + 1; i++)
				{

					FRotator RotToShoot = StartRotator;
					RotToShoot.Yaw = StartRotator.Yaw + (Angle / UKismetMathLibrary::Conv_IntToFloat(NumOfShots)) * i ;
					FVector End = PointToShootSF + RotToShoot.Vector() * ShotLength;

					RotToShoot.Yaw = StartRotator.Yaw + Angle / 2.f - StartAngle / 2.f;

					RotToShoot.Yaw = RotToShoot.Yaw + (StartAngle / UKismetMathLibrary::Conv_IntToFloat(NumOfShots)) * i;

					FVector Start = FirstPoint + RotToShoot.Vector() * 100.f;

					UObject* TestObject = MultiTrace(Start, End, ECC_GameTraceChannel5);

					if (TestObject != NULL)
					{
						ActorArray.Add(TestObject);
					}


				}
				int ItemsFound = 0;
				while (ActorArray.Num() != 0)
				{
					ItemsFound = 0;
					UObject* TestActor;
					TestActor = ActorArray[0];
					if (TestActor->IsValidLowLevel() && TestActor->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
					{
						for (int ii = 1; ii < ActorArray.Num(); ii++)
						{
							if (TestActor == ActorArray[ii])
							{
								ItemsFound++;
							}
						}
						IDamageIntarface::Execute_DoDamage(TestActor, ItemsFound * SFDamage, InstigatorSF, InstigatorSF->GetCharacter(), EDamageType::VE_ShotGun);

						ACharacter* TestChar = Cast<ACharacter>(TestActor);
						if(TestChar)
							if (DamageParticleSF->IsValidLowLevel())
							{

							
								//UGameplayStatics::SpawnEmitterAttached(DamageParticleSF,
								//	TestChar->GetMesh(), 
								//	FVector(0, 0, 0),
								//	FRotator(0, 0, 0),
								//	EAttachLocation::SnapToTarget);

								UParticleSystemComponent* TestParticle = UGameplayStatics::SpawnEmitterAtLocation(TestChar->GetWorld(), 
									DamageParticleSF, 
									TestChar->GetMesh()->GetComponentLocation(), 
									TestChar->GetMesh()->GetComponentRotation());

								//TestParticle->AttachToComponent(TestChar->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

							}

						//TestChar->GetMesh()->GetComponentLocation()
						//TestChar->GetMesh()->GetComponentRotation()
					}
					ActorArray.Remove(TestActor);
				}


				if (FireParticleSF->IsValidLowLevel())
				{
					UGameplayStatics::SpawnEmitterAtLocation(Char, FireParticleSF, PointToShootSF, RotToShootSF);
				}

				Ammo -= 5;
				return true;
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}



UObject* UMC_Rifle::MultiTrace(FVector StartPointToShoot, FVector EndPointToShoot, ECollisionChannel PrefferedChannel)
{
	UObject* FinaleObject = NULL;

	if (Char->IsValidLowLevel())
	{
		UWorld* World = Char->GetWorld();
		if (World != NULL)
		{

			TArray<FHitResult> HitOut;

			FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, Char);


			if (bShowShotGunRays)
			{
				const FName TraceTag("ShotgunTraseTag");

				World->DebugDrawTraceTag = TraceTag;

				TraceParams.TraceTag = TraceTag;
			}

			World->LineTraceMultiByChannel(HitOut, StartPointToShoot, EndPointToShoot, PrefferedChannel, TraceParams);

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
								if (TestCharPawn->GetTeam() != Char->GetTeam())
								{
									if (HitOut[i].GetComponent()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
									{
										//Тест на компонент
										FinaleObject = HitOut[i].GetComponent();
										break;
									}

									else
									{
										FinaleObject = HitOut[i].GetActor();
										break;
									}

								}
							}

							else
							{
								if (HitOut[i].GetComponent()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
								{
									FinaleObject = HitOut[i].GetComponent();					
									break;
								}
								else
								{
									FinaleObject = HitOut[i].GetActor();							
									break;
								}

							}

						}
						else
						{
							if (HitOut[i].GetComponent()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
							{
								//Тест на компонент
								FinaleObject = HitOut[i].GetComponent();					
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
							break;
						}
					}
				}


			}

		}
	}


	return FinaleObject;
}