// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "TrailSMC.h"
#include "Trail30.h"


// Sets default values for this component's properties
UTrail30::UTrail30()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTrail30::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTrail30::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTrail30::StartTrail(TArray<UStaticMeshComponent*> InputSMCArrayRef, bool UseArrayRef, UStaticMeshComponent* SMCReference, float TrailLifeTime, int MaxNumberOfSMCs, bool LengthTest, float vRef, float rRef)
{
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{

		IsLengthTest = false;
		if (SMCReference->IsValidLowLevel() && TrailMaterial != NULL && TrailTimeLength != 0 && InputSMCArrayRef.Num() != 0)
		{
			if (UseArrayRef&& InputSMCArrayRef.Num() != 0)
			{
				InputSMCArray = InputSMCArrayRef;
				UseArray = UseArrayRef;
			}
			MaxNumOfSMC = MaxNumberOfSMCs;
			OldSpawnDelay = SpawnDelay;
			SMC = SMCReference;

			if (LengthTest)
			{

				IsLengthTest = LengthTest;

				MaxVL = vRef;
				MaxRL = rRef;
				CreateSMC();
			}

			if (!World->GetTimerManager().IsTimerActive(SpawnTimer))
			{
				World->GetTimerManager().SetTimer(SpawnTimer, this, &UTrail30::TrailCicle, SpawnDelay, true, SpawnDelay);
			}
			if (TrailLifeTime > 0.2f)
			{
				World->GetTimerManager().SetTimer(SpawnTimer, this, &UTrail30::FinishTrail, TrailLifeTime);
			}
		}
	}
}

void UTrail30::TrailCicle()
{
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		if (IsLengthTest)
		{
			float TestValue = 0.f;



			if (MaxVL > 0.1)
			{
				TestValue = TestValue + (SMC->GetComponentLocation() - LastLoc).Size() / MaxVL;
			}
			if (MaxRL > 0.1)
			{
				TestValue = TestValue + GetRotLength(SMC->GetComponentRotation() - LastRot) / MaxRL;
			}
			if (TestValue > 1.f)
			{
				CreateSMC();
			}

		}
		else
		{
			CreateSMC();
			
		}
		

		if (MaxNumOfSMC != 0)
		{
			if (SMCArray.Num() > MaxNumOfSMC)
			{
				for (int i = 0; SMCArray.Num() >= MaxNumOfSMC; i++)
				{
					if (SMCArray[0]->IsValidLowLevel())
					{
						SMCArray[0]->DestroyComponent();
					}
					SMCArray.RemoveAt(0);
				}
			}
		}

		if (OldSpawnDelay != SpawnDelay)
		{
			OldSpawnDelay = SpawnDelay;
			World->GetTimerManager().SetTimer(SpawnTimer, this, &UTrail30::TrailCicle, SpawnDelay, true, SpawnDelay);
		}
		
	}
}

void UTrail30::FinishTrail()
{
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{

		World->GetTimerManager().ClearTimer(SpawnTimer);
	}
}

TArray<UStaticMeshComponent*> UTrail30::GetSMCArray()
{
	return SMCArray;
}

void UTrail30::CreateSMC()
{
	if (UseArray)
	{
		
		for (int ii = 0; ii < InputSMCArray.Num(); ii++)
		{
			LastSMC = NewObject<UTrailSMC>(GetOwner());
			LastSMC->OnComponentCreated();
			LastSMC->RegisterComponent();

			LastSMC->SetMaterial(0, TrailMaterial);

			UTrailSMC* CastSMC = Cast<UTrailSMC>(LastSMC);
			LastSMC->SetStaticMesh(InputSMCArray[ii]->StaticMesh);

			if (CastSMC)
			{
				CastSMC->StartScale = StartTrailScale;
				CastSMC->EndScale = EndTrailScale;
				CastSMC->StartTimer(TrailTimeLength, this);
			}
			 
			LastSMC->SetWorldTransform(InputSMCArray[ii]->GetComponentTransform());

			SMCArray.Add(LastSMC);
		}
		LastLoc = SMC->GetComponentLocation();
		LastRot = SMC->GetComponentRotation();

	}
	else
	{
		LastSMC = NewObject<UTrailSMC>(GetOwner());
		LastSMC->OnComponentCreated();
		LastSMC->RegisterComponent();

		LastSMC->SetMaterial(0, TrailMaterial);

		UTrailSMC* CastSMC = Cast<UTrailSMC>(LastSMC);
		LastSMC->SetStaticMesh(SMC->StaticMesh);

		if (CastSMC)
		{

			CastSMC->StartTimer(TrailTimeLength, this);
		}



		if (SMCArray.Num() != 0)
		{
			FTransform MeshTransform = UKismetMathLibrary::SelectTransform(SMCArray.Last()->GetComponentTransform(), SMC->GetComponentTransform(), SMCArray.Last()->IsValidLowLevel());
			LastSMC->SetWorldTransform(UKismetMathLibrary::TLerp(MeshTransform, SMC->GetComponentTransform(), 0.5f));
		}
		else
		{
			LastSMC->SetWorldTransform(SMC->GetComponentTransform());
		}





		SMCArray.Add(LastSMC);

		LastLoc = LastSMC->GetComponentLocation();
		LastRot = LastSMC->GetComponentRotation();
	}

}

void UTrail30::ClearAllTrail()
{
	UWorld* World = GetOwner()->GetWorld();

	for (int i = 0; i < SMCArray.Num(); i++)
	{
		if (SMCArray[i]->IsValidLowLevel())
		{
			SMCArray[i]->DestroyComponent();
		}
	}
	SMCArray.Empty();
	
	if (World != NULL)
	{
		World->GetTimerManager().ClearTimer(SpawnTimer);
		World->GetTimerManager().ClearTimer(FinishTimer);
	}
}

void UTrail30::RemoveSMC(UStaticMeshComponent* TrailSMCRef)
{
	
	SMCArray.Remove(TrailSMCRef);
}


float UTrail30::GetRotLength(FRotator RotRef)
{
	return UKismetMathLibrary::Sqrt(powf(RotRef.Roll, 2.f) + powf(RotRef.Yaw, 2.f) + powf(RotRef.Pitch, 2.f));
}

void UTrail30::OnDestroy()
{
	ClearAllTrail();
	DestroyComponent();
}