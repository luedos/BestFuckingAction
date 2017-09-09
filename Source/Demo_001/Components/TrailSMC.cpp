// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Trail30.h"
#include "TrailSMC.h"


UTrailSMC::UTrailSMC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = true;

	SetCollisionProfileName(FName(TEXT("IgnorAll")));

	StartScale = FVector(1.f, 1.f, 1.f);
	EndScale = FVector(1.f, 1.f, 1.f);
	// ...
}


// Called when the game starts
void UTrailSMC::BeginPlay()
{
	Super::BeginPlay();



}


// Called every frame
void UTrailSMC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Period += DeltaTime;

	if (Mat->IsValidLowLevel())
	{
		Mat->SetVectorParameterValue("Color", UKismetMathLibrary::LinearColorLerp(StartSMCColor, EndSMCColor, Period/SMCLifeTime));
	}

	if (!(StartScale == FVector(0.f, 0.f, 0.f) && EndScale == FVector(0.f, 0.f, 0.f)))
	{
		SetWorldScale3D(UKismetMathLibrary::VLerp(StartScale, EndScale, Period / SMCLifeTime));
	}
}

void UTrailSMC::StartTimer(float LifeTime, UTrail30* TrailComponentReference)
{
	if (TrailComponentReference != NULL)
	{
		TrailComponent = TrailComponentReference;
		StartSMCColor = TrailComponent->StartColor;
		EndSMCColor = TrailComponent->EndColor;

	}
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		
		World->GetTimerManager().SetTimer(DestroyTimer, this, &UTrailSMC::DestroySMC, LifeTime);


	}
	SMCLifeTime = LifeTime;
	Period = 0.f;
	Mat = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, GetMaterial(0));
	SetMaterial(0, Mat);
	Mat->SetVectorParameterValue("Color", StartSMCColor);
	
}


void UTrailSMC::DestroySMC()
{
	if (TrailComponent->IsValidLowLevel())
	{
		TrailComponent->RemoveSMC(this);
	}
	DestroyComponent();
}