// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Components/WeaponSMC.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "MC_LaserBeam.h"



UMC_LaserBeam::UMC_LaserBeam()
{

	FireRange = 3000.f;
	RicochetRange = 2000.f;
	RicochetAngle = 30.f;
	NumOfRicochtCheck = 30;
}


bool UMC_LaserBeam::OnCreated(ACharPawn* CharRef)
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
				SMC->LookAtSceneComponent(SMC);
				SMC->IsLookAtPoint = true;
				SMC->StartRotate(180.f, 10);
			}
			OnCreated_BNE();

			return false;
		}
		else
		{
			return false;
		}

}

bool UMC_LaserBeam::FirstFire(APlayerController * InstigatorFF, FVector PointToShootFF, FRotator RotToShootFF)
{
	if (Char->IsValidLowLevel())
	{
		if (BackPackAmmo > 0)
		{
			UWorld* World = Char->GetWorld();
			if (World != NULL)
			{
			
				if (FireParticleFF->IsValidLowLevel())
				{
					UParticleSystemComponent* TestParticle = UGameplayStatics::SpawnEmitterAtLocation(this, FireParticleFF, PointToShootFF - RotToShootFF.Vector() * 100.f, RotToShootFF, true);
					TestParticle->SetColorParameter("ParticleColor", WeaponColor);
					//TestParticle->SetBeamTargetPoint(0, PointToShootFF, 0);
					TestParticle->SetVectorParameter("BeamTarget", FVector(100.f, 0, 0));
				}

				bool bRicoshet = false;

				TArray<FHitResult> HitOut;

				

				FVector EndPoint = PointToShootFF + RotToShootFF.Vector() * FireRange;

				FVector EndLocation = EndPoint;

				//World->LineTraceMultiByChannel(HitOut, PointToShootFF, EndPoint, ECC_GameTraceChannel5, TraceParams);
				TArray<AActor*> ActorToIgnor;

				UKismetSystemLibrary::SphereTraceMulti_NEW(this, PointToShootFF, EndPoint, 25, 
					ETraceTypeQuery::TraceTypeQuery3, true, ActorToIgnor, EDrawDebugTrace::None, HitOut, true);

				if (HitOut.Num() != 0)
				{
					
					UObject* FinaleObject = NULL;

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
											IDamageIntarface::Execute_DoDamage(HitOut[i].GetComponent(), 500.f, Char->GetTeam(), InstigatorFF->GetCharacter(), EDamageType::VE_LaserBeam);
											EndLocation = HitOut[i].Location;
											break;
										}

										else
										{
											IDamageIntarface::Execute_DoDamage(HitOut[i].GetActor(), 500.f, Char->GetTeam(), InstigatorFF->GetCharacter(), EDamageType::VE_LaserBeam);
											EndLocation = HitOut[i].Location;
											break;
										}

									}
								}

								else
								{
									if (HitOut[i].GetComponent()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
									{
										IDamageIntarface::Execute_DoDamage(HitOut[i].GetComponent(), 500.f, Char->GetTeam(), InstigatorFF->GetCharacter(), EDamageType::VE_LaserBeam);
										EndLocation = HitOut[i].Location;
										break;
									}
									else
									{
										IDamageIntarface::Execute_DoDamage(HitOut[i].GetActor(), 500.f, Char->GetTeam(), InstigatorFF->GetCharacter(), EDamageType::VE_LaserBeam);
										EndLocation = HitOut[i].Location;
										break;
									}

								}

							}
							else
							{
								if (HitOut[i].GetComponent()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
								{
									//Тест на компонент
									IDamageIntarface::Execute_DoDamage(HitOut[i].GetComponent(), 500.f, Char->GetTeam(), InstigatorFF->GetCharacter(), EDamageType::VE_LaserBeam);
									EndLocation = HitOut[i].Location;
									break;
								}
								else
								{
									if (HitOut[i].bBlockingHit)
									{
										Ricochet(InstigatorFF, HitOut[i].Normal, HitOut[i].Location, PointToShootFF, RicochetAngle, NumOfRicochtCheck);
										EndLocation = HitOut[i].Location;
										bRicoshet = true;
										break;
									}
								}
							}
						}
						else
						{
							if (HitOut[i].bBlockingHit)
							{
								Ricochet(InstigatorFF, HitOut[i].Normal, HitOut[i].Location, PointToShootFF, RicochetAngle, NumOfRicochtCheck);
								EndLocation = HitOut[i].Location;
								bRicoshet = true;
								break;
							}
						}
					}
				}


				SpawnParticle_BNE(PointToShootFF, EndLocation, bRicoshet);

				BackPackAmmo -= 1;

				if (Char->IsValidLowLevel() && FFSound_Fire->IsValidLowLevel())
					UGameplayStatics::PlaySoundAtLocation(Char, FFSound_Fire, PointToShootFF);


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

bool UMC_LaserBeam::SecondFire(APlayerController * InstigatorSF, FVector PointToShootSF, FRotator RotToShootSF)
{
	return false;
}

void UMC_LaserBeam::Ricochet(APlayerController* FireInstigator,FVector Normal, FVector Point, FVector ActorPos, float Angle, int NumOfChecks)
{
	
	if (Char->IsValidLowLevel())
	{
		UWorld* World = Char->GetWorld();
		if (World != NULL)
		{
			DesiredObject = NULL;
			int DesiredLevel = -1;
			
			int TestsFromMiddle = UKismetMathLibrary::Divide_IntInt(NumOfChecks, 2);

			

			float StepSize = Angle / UKismetMathLibrary::Conv_IntToFloat(NumOfChecks);

			float StartYawRot = (Normal.Rotation().Yaw * 2.f) - UKismetMathLibrary::FindLookAtRotation(Point, ActorPos).Yaw;

			FVector DesiredLocation = FRotator(0.f, StartYawRot, 0.f).Vector() * RicochetRange + Point;

			StartYawRot = StartYawRot - Angle / 2.f;

			if (NumOfChecks > 0)
			{
				for (int i = 0; i < NumOfChecks; i++)
				{
					
					UObject* TestObject = NULL;
					FVector TestLocation;
					FVector EndPoint = UKismetMathLibrary::Multiply_VectorFloat(FRotator(0.f, StartYawRot + StepSize * UKismetMathLibrary::Conv_IntToFloat(i), 0.f).Vector(), RicochetRange) + Point;

					FVector Start = Point + Normal * 30;

					int TestInt = BeamFire(TestObject, TestLocation, Start, EndPoint, ECC_GameTraceChannel5);

					if (TestInt > DesiredLevel)
					{
						DesiredObject = TestObject;
						DesiredLevel = TestInt;
						DesiredLocation = TestLocation;
						TestsFromMiddle = UKismetMathLibrary::Abs_Int(UKismetMathLibrary::Divide_IntInt(NumOfChecks, 2) - i);
					}
					
					if (TestInt == DesiredLevel)
					{
						if (TestsFromMiddle > UKismetMathLibrary::Abs_Int(UKismetMathLibrary::Divide_IntInt(NumOfChecks, 2) - i))
						{
							DesiredObject = TestObject;
							DesiredLevel = TestInt;
							DesiredLocation = TestLocation;
							TestsFromMiddle = UKismetMathLibrary::Abs_Int(UKismetMathLibrary::Divide_IntInt(NumOfChecks, 2) - i);
						}
					}
				}
				if (DesiredObject->IsValidLowLevel() && DesiredObject->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
				{
					IDamageIntarface::Execute_DoDamage(DesiredObject, 500.f, Char->GetTeam(), FireInstigator->GetCharacter(), EDamageType::VE_LaserBeam);
					
				}
				SpawnParticle_BNE(Point, DesiredLocation, false);
			}

		}
	}
}

int UMC_LaserBeam::BeamFire(UObject*& ObjectRef, FVector& ShotedPoint, FVector Start, FVector End, ECollisionChannel PrefferedChannel)
{
	UObject* FinaleObject = NULL;
	int FinaleDisirebility = -1;
	FVector EndVector = End;

	if (Char->IsValidLowLevel())
	{
		UWorld* World = Char->GetWorld();
		if (World != NULL)
		{

			TArray<FHitResult> HitOut;

			//FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, Char);



			//World->LineTraceMultiByChannel(HitOut, Start, End, PrefferedChannel, TraceParams);

			TArray<AActor*> ActorToIgnor;

			UKismetSystemLibrary::SphereTraceMulti_NEW(this, Start, End, 25,
				ETraceTypeQuery::TraceTypeQuery3, true, ActorToIgnor, EDrawDebugTrace::None, HitOut, true);

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

										UShield* TestShield1 = Cast<UShield>(FinaleObject);
										if (TestShield1)
										{
											FinaleDisirebility = 1;
										}
										else
										{
											UKritComponent* TestKrit1 = Cast<UKritComponent>(FinaleObject);
											if (TestKrit1)
											{
												FinaleDisirebility = 3;
											}
											else
											{
												FinaleDisirebility = 1;
											}
										}
										EndVector = HitOut[i].ImpactPoint;
										break;
									}

									else
									{
										FinaleObject = HitOut[i].GetActor();
										FinaleDisirebility = 2;
										EndVector = HitOut[i].ImpactPoint;
										break;
									}

								}
							}

							else
							{
								if (HitOut[i].GetComponent()->GetClass()->ImplementsInterface(UDamageIntarface::StaticClass()))
								{
									FinaleObject = HitOut[i].GetComponent();

									UShield* TestShield1 = Cast<UShield>(FinaleObject);
									if (TestShield1)
									{
										FinaleDisirebility = 1;
									}
									else
									{
										UKritComponent* TestKrit1 = Cast<UKritComponent>(FinaleObject);
										if (TestKrit1)
										{
											FinaleDisirebility = 3;
										}
										else
										{
											FinaleDisirebility = 1;
										}
									}
									EndVector = HitOut[i].ImpactPoint;
									break;
								}
								else
								{
									FinaleObject = HitOut[i].GetActor();
									FinaleDisirebility = 1;
									EndVector = HitOut[i].ImpactPoint;
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

								UShield* TestShield1 = Cast<UShield>(FinaleObject);
								if (TestShield1)
								{
									FinaleDisirebility = 1;
								}
								else
								{
									UKritComponent* TestKrit1 = Cast<UKritComponent>(FinaleObject);
									if (TestKrit1)
									{
										FinaleDisirebility = 3;
									}
									else
									{
										FinaleDisirebility = 1;
									}
								}
								EndVector = HitOut[i].ImpactPoint;
								break;
							}
							else
							{
								if (HitOut[i].bBlockingHit)
								{
									EndVector = HitOut[i].ImpactPoint;
									break;
								}
							}
						}
					}
					else
					{
						if (HitOut[i].bBlockingHit)
						{
							EndVector = HitOut[i].ImpactPoint;
							break;
						}
					}
				}

				
			}

		}
	}
	
	
	ShotedPoint = EndVector;
	ObjectRef = FinaleObject;
	return FinaleDisirebility;
}


void  UMC_LaserBeam::SpawnParticle_BNE_Implementation(FVector Start, FVector End, bool bSpawnHitParticle)
{
	

	if (FireParticleSF->IsValidLowLevel())
	{
	

		UParticleSystemComponent* TestParticle = UGameplayStatics::SpawnEmitterAtLocation(this, FireParticleSF, Start, FRotator(0, 0, 0), true);

		TestParticle->SetColorParameter("ParticleColor", WeaponColor);
		TestParticle->SetVectorParameter("Target", End - Start);
		TestParticle->SetEmitterEnable("Impact", bSpawnHitParticle);
	}
}