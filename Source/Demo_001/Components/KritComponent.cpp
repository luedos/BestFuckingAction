// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "KritComponent.h"



UKritComponent::UKritComponent()
{
	KritMultiplier = 4.f;
}

void UKritComponent::OnKrit(float InDamage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType)
{
	if (Char->IsValidLowLevel())
	{
		IDamageIntarface::Execute_DoDamage(Char, InDamage * KritMultiplier, DamageFromTeam, Couser, DamageType);
		OnKrit_BNE(InDamage, DamageFromTeam, Couser, DamageType);
	}
}
void UKritComponent::DoDamage_Implementation(float Damage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType)
{
	OnKrit(Damage, DamageFromTeam, Couser, DamageType);
}

void UKritComponent::OnCreatedKC(ACharPawn* CharRef)
{
	Char = CharRef;
}
