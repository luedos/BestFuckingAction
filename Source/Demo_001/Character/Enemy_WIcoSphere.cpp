// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Engine.h"
#include "Components/ArrowComponent.h"
#include "Components/Shield.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy_WIcoSphere.h"


AEnemy_WIcoSphere::AEnemy_WIcoSphere()
{
	ComponentsFaceArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FaceArrowComponent"));
	ComponentsFaceArrow->SetupAttachment(RootComponent);

	MaxHP = 250;
	HP = 250;

	ArrowInterpSpeed = 5;
}

void AEnemy_WIcoSphere::ChangeArrowInterpSpeed(float NewSpeed)
{
	ArrowInterpSpeed = NewSpeed;
}

void AEnemy_WIcoSphere::ShieldUp(float InDelay)
{

	ShieldComponent = NewObject<UShield>(this, UsingShield);

	ShieldComponent->OnComponentCreated();
	ShieldComponent->RegisterComponent();

	ShieldComponent->OnCreated(this);

	ShieldComponent->AttachToComponent(ComponentsFaceArrow, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	ShieldComponent->SetWorldRotation(ComponentsFaceArrow->GetComponentRotation());

	ShieldComponent->SetWorldScale3D(FVector(1.4f, 1.4f, 1.4f));

	if (InDelay > 0.1f)
	{
		GetWorldTimerManager().SetTimer(ShieldTimer, this, &AEnemy_WIcoSphere::ShieldDown, InDelay);
	}

}

void AEnemy_WIcoSphere::ShieldDown()
{
	if (ShieldComponent->IsValidLowLevel())
	{
		ShieldComponent->OnDownBNE();
	}
}


bool AEnemy_WIcoSphere::InterpFaceArrow(float TimeDelay, FVector ToPoint)
{
	if (!IsInDelay)
	{
		ComponentsFaceArrow->SetWorldRotation(UKismetMathLibrary::RInterpTo(
			FRotator(0, ComponentsFaceArrow->GetComponentRotation().Yaw, 0), 
			FRotator(0, UKismetMathLibrary::FindLookAtRotation(ComponentsFaceArrow->GetComponentLocation(), ToPoint).Yaw, 0), 
			TimeDelay, ArrowInterpSpeed));

	}
	else
		return false;


	return true;
}