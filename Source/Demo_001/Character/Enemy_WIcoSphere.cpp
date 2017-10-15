// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Engine.h"
#include "Components/ArrowComponent.h"
#include "Components/Shield.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Enemy_WIcoSphere.h"


AEnemy_WIcoSphere::AEnemy_WIcoSphere()
{


	MaxHP = 250;
	HP = 250;

	ArrowInterpSpeed = 5;

	ArrowRotSpeed = 360;
}


void AEnemy_WIcoSphere::ShieldUp(float InDelay)
{

	ShieldComponent = NewObject<UShield>(this, UsingShield);

	ShieldComponent->OnComponentCreated();
	ShieldComponent->RegisterComponent();

	ShieldComponent->OnCreated(this);

	ShieldComponent->AttachToComponent(FaceArrow, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	ShieldComponent->SetWorldRotation(FaceArrow->GetComponentRotation());

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
