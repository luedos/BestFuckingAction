// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "WeaponPickUp.h"


AWeaponPickUp::AWeaponPickUp()
{

	SetCanPickUp(true);
}

// Called when the game starts or when spawned
void AWeaponPickUp::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeaponPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

