// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Shield.h"



UShield::UShield()
{
	SetCollisionProfileName(FName(TEXT("Shield")));

	ShieldHP = 500.f;

	SpeedNerf = 0.7f;
}

void UShield::OnCreated(ACharacter * CharRef)
{
	Char = CharRef;

	CharWalkSpeed = Char->GetCharacterMovement()->MaxWalkSpeed;

	Char->GetCharacterMovement()->MaxWalkSpeed = CharWalkSpeed * SpeedNerf;

	OnCreatedBNE();
}

void UShield::OnCreatedBNE_Implementation()
{
}

void UShield::OnDestroyBNE_Implementation()
{}

void UShield::OnDownBNE_Implementation()
{
}



void UShield::RemoveHP(float HPToRemove)
{
	ShieldHP = ShieldHP - HPToRemove;

	if (ShieldHP <= 0)
	{
		OnDestroyBNE();
	}
}