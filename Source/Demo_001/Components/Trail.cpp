// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "Trail.h"


// Sets default values for this component's properties
UTrail::UTrail()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTrail::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTrail::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTrail::StartTrail(float TrailLength, UStaticMeshComponent* SMCReference)
{
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		SMC = SMCReference;
		if (!World->GetTimerManager().IsTimerActive(TrailTimer))
		{
			DeleteDelay = TrailTimeLength / NumOfTrailMeshes;
			World->GetTimerManager().SetTimer(TrailTimer, this, &UTrail::TrailCicle,  DeleteDelay);

		}
		if (TrailLength > 0.1f)
		{
			World->GetTimerManager().SetTimer(FinishTrailTimer, this, &UTrail::FinishTrail,  TrailLength);
		}

	}
}

void UTrail::CreateMeshComponent()
{
	LastSMC = NewObject<UStaticMeshComponent>(GetOwner());
	LastSMC->OnComponentCreated();
	LastSMC->RegisterComponent();



	LastSMC->SetStaticMesh(SMC->StaticMesh);

	if (SMCsArray.Num() != 0)
	{
		FTransform MeshTransform = UKismetMathLibrary::SelectTransform(SMCsArray.Last()->GetComponentTransform(), SMC->GetComponentTransform(), SMCsArray.Last()->IsValidLowLevel());
		LastSMC->SetWorldTransform(UKismetMathLibrary::TLerp(MeshTransform, SMC->GetComponentTransform(), 0.5f));
	}
	else
	{
		LastSMC->SetWorldTransform(SMC->GetComponentTransform());
	}
	LastSMC->SetMaterial(0, TrailMaterial);

	SMCsArray.Add(LastSMC);
}

void UTrail::DestroyMeshComponent()
{
	SMCsArray[0]->DestroyComponent();
	SMCsArray.RemoveAt(0);
	DeleteDelayArray.RemoveAt(0);


}

void UTrail::TrailCicle()
{
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		CreateMeshComponent();
		DeleteDelayArray.Add(DeleteDelay);
		World->GetTimerManager().SetTimer(TrailTimer, this, &UTrail::TrailCicle, DeleteDelay);
		DeleteDelay = TrailTimeLength / NumOfTrailMeshes;

		if (SMCsArray.Num() >= NumOfTrailMeshes)
		{
			if (SMCsArray.Num() == NumOfTrailMeshes)
			{
				DestroyMeshComponent();
			}

			if (SMCsArray.Num() > NumOfTrailMeshes)
			{
				while (SMCsArray.Num() > NumOfTrailMeshes)
				{
					DestroyMeshComponent();
				}
			}
		}

	}
}

void UTrail::DeleteCicle()
{
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		DestroyMeshComponent();
		if (SMCsArray.Num() != 0)
		{
			World->GetTimerManager().SetTimer(DestroyTimer, this, &UTrail::DeleteCicle,  DeleteDelayArray[0]);
		}
	}
}

void UTrail::FinishTrail()
{
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		if (World->GetTimerManager().IsTimerActive(TrailTimer))
		{
			GetOwner()->GetWorld()->GetTimerManager().ClearTimer(TrailTimer);
		}
		World->GetTimerManager().SetTimer(DestroyTimer, this, &UTrail::DeleteCicle,  DeleteDelayArray[0]);
	}
}



void UTrail::TestFunction(UStaticMeshComponent* TestSMCReference)
{
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		SMC = TestSMCReference;

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Here I am "));

		CreateMeshComponent();
	}
}

void UTrail::ClearAllTrail()
{
	UWorld* World = GetOwner()->GetWorld();
	for (int i = 0; i < SMCsArray.Num(); i++)
	{
		SMCsArray[i]->DestroyComponent();
	}
	SMCsArray.Empty();
	DeleteDelayArray.Empty();
	if (World != NULL)
	{
		World->GetTimerManager().ClearTimer(TrailTimer);
		World->GetTimerManager().ClearTimer(FinishTrailTimer);
		World->GetTimerManager().ClearTimer(DestroyTimer);
	}


}

TArray<UStaticMeshComponent*> UTrail::GetMeshArray()
{
	return SMCsArray;
}

TArray<float> UTrail::GetDelayArray()
{
	return DeleteDelayArray;
}