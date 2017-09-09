// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/MC_Char.h"
#include "Engine.h"
#include "WeaponSMC.h"



UWeaponSMC::UWeaponSMC()
{

	PrimaryComponentTick.bCanEverTick = true;

	SetCollisionProfileName(FName(TEXT("IgnorAll")));

	LookAtState = ESMCLookAt::VE_SocketRotation;
}




// Called every frame
void UWeaponSMC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsLookAtPoint != NULL)
	{
		if (IsLookAtPoint)
		{
			LookAtPoint();
		}
	}
}

void UWeaponSMC::OnCreated(ACharacter* CharRef, UStaticMesh* SMRef, UStaticMesh* SelfSM, UMaterial* SMMaterial)
{
	Char = CharRef;

	SetStaticMesh(SelfSM);

	if (GetStaticMesh()->IsValidLowLevel() && Char->IsValidLowLevel() && SMRef->IsValidLowLevel() && SMMaterial->IsValidLowLevel())
	{
		



		UStaticMeshSocket* SMSocket1 = GetStaticMesh()->FindSocket("WeaponSMC1");
		if (SMSocket1 != NULL)
		{
			LastSMC = NewObject<UStaticMeshComponent>(Char);
			LastSMC->OnComponentCreated();
			LastSMC->RegisterComponent();

			LastSMC->SetStaticMesh(SMRef);

			LastSMC->SetMaterial(0, SMMaterial);

			LastSMC->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld,false), "WeaponSMC1");

			LastSMC->SetCollisionProfileName(FName(TEXT("IgnorAll")));

			ComponentsArray.Add(LastSMC);
		}
		UStaticMeshSocket* SMSocket2 = GetStaticMesh()->FindSocket("WeaponSMC2");
		if (SMSocket2 != NULL)
		{
			LastSMC = NewObject<UStaticMeshComponent>(Char);
			LastSMC->OnComponentCreated();
			LastSMC->RegisterComponent();

			LastSMC->SetStaticMesh(SMRef);

			LastSMC->SetMaterial(0, SMMaterial);

			LastSMC->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false), "WeaponSMC2");

			LastSMC->SetCollisionProfileName(FName(TEXT("IgnorAll")));

			ComponentsArray.Add(LastSMC);
		}
		UStaticMeshSocket* SMSocket3 = GetStaticMesh()->FindSocket("WeaponSMC3");
		if (SMSocket3 != NULL)
		{
			LastSMC = NewObject<UStaticMeshComponent>(Char);
			LastSMC->OnComponentCreated();
			LastSMC->RegisterComponent();

			LastSMC->SetStaticMesh(SMRef);

			LastSMC->SetMaterial(0, SMMaterial);

			LastSMC->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false), "WeaponSMC3");

			LastSMC->SetCollisionProfileName(FName(TEXT("IgnorAll")));

			ComponentsArray.Add(LastSMC);
		}
	}
}

void UWeaponSMC::StartRotate(float RotRate, float StartRotInterpSpeedRef)
{

	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		InterpSpeed = StartRotInterpSpeedRef;
		if (!World->GetTimerManager().IsTimerActive(RotationTimer))
		{
			RotationRate = RotRate;
			OldRotationRate = RotationRate;
			World->GetTimerManager().SetTimer(RotationTimer, this, &UWeaponSMC::AddRelativeRot, 1/RotationRate, true, 1/RotationRate);
		}
		else
		{
			RotationRate = RotRate;
		}
	}
}

void UWeaponSMC::AddRelativeRot_BNE_Implementation()
{}

void UWeaponSMC::AddRelativeRot()
{
	//AddRelativeRotation(FRotator(0.f, RotationScale, 0.f));


	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		AddRelativeRot_BNE();

		if (UKismetMathLibrary::NearlyEqual_FloatFloat(RotationRate, 0, 0.7f) && UKismetMathLibrary::NearlyEqual_FloatFloat(OldRotationRate, 0, 2))
		{
			World->GetTimerManager().ClearTimer(RotationTimer);
		}
		else
		{
			if (OldRotationRate != RotationRate)
			{
				OldRotationRate = UKismetMathLibrary::FInterpTo(OldRotationRate, RotationRate, OldRotationRate, InterpSpeed);
				World->GetTimerManager().SetTimer(RotationTimer, this, &UWeaponSMC::AddRelativeRot, 1 / OldRotationRate, true, 1 / OldRotationRate);
			}
		}
	}
}

void UWeaponSMC::EndRotation(float EndRotInterpSpeedRef)
{

	RotationRate = 0.f;
	InterpSpeed = EndRotInterpSpeedRef;
}



void UWeaponSMC::SetRotationScale(float RotScale)
{
	RotationScale = RotScale;
}

void UWeaponSMC::OnDestroy()
{
	DestroyComponent(true);
}

void UWeaponSMC::LookAtChar(ACharacter * Character)
{
	LookAtCharRef = Character;
	LookAtState = ESMCLookAt::VE_AtChar;
}

void UWeaponSMC::LookAtSceneComponent(USceneComponent * SceneComp)
{
	LookAtSceneComponentRef = SceneComp;
	LookAtState = ESMCLookAt::VE_AtSceneComponent;
}

void UWeaponSMC::LookAtRotation(FRotator Rotation)
{
	LookAtRotatorRef = Rotation;
	LookAtState = ESMCLookAt::VE_AtRotation;
}

void UWeaponSMC::LookBySocket()
{
	LookAtState = ESMCLookAt::VE_SocketRotation;
}

TArray<UStaticMeshComponent*> UWeaponSMC::GetComponentsArray()
{
	return ComponentsArray;
}

void UWeaponSMC::LookAtPoint()
{
	switch (LookAtState)
	{
	case ESMCLookAt::VE_AtChar:
		if (LookAtCharRef->IsValidLowLevel())
		{
			AMC_Char* CastChar = Cast<AMC_Char>(LookAtCharRef);
			if (CastChar)
			{
				for (int i = 0; i < ComponentsArray.Num(); i++)
				{
					if (ComponentsArray[i]->IsValidLowLevel())
					{
						ComponentsArray[i]->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(ComponentsArray[i]->GetComponentLocation(), CastChar->GetCharLookPoint()));
					}
				}
			}
		}

		break;
	case ESMCLookAt::VE_AtSceneComponent:
		if (LookAtSceneComponentRef->IsValidLowLevel())
		{
			for (int i = 0; i < ComponentsArray.Num(); i++)
			{
				if (ComponentsArray[i]->IsValidLowLevel())
				{
					ComponentsArray[i]->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(ComponentsArray[i]->GetComponentLocation(), LookAtSceneComponentRef->GetComponentLocation()));
				}
			}
		}

		break;
	case ESMCLookAt::VE_AtRotation:
		for (int i = 0; i < ComponentsArray.Num(); i++)
		{
			if (ComponentsArray[i]->IsValidLowLevel())
			{
				ComponentsArray[i]->SetWorldRotation(LookAtRotatorRef);
			}
		}
		break;
	case ESMCLookAt::VE_SocketRotation:

		for (int i = 0; i < ComponentsArray.Num(); i++)
		{
			if (ComponentsArray[i]->IsValidLowLevel())
			{
				
				ComponentsArray[i]->SetWorldRotation(GetSocketRotation(ComponentsArray[i]->GetAttachSocketName()));
			}
		}

		break;
	default:
		break;
	}
	
}
