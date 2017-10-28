// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Character/MC_Char.h"
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

void AWeaponPickUp::PickUpFunc_Implementation(ACharPawn* FromChar)
{
	if (FromChar->IsValidLowLevel() && WeaponObject->IsValidLowLevel())
	{
		AMC_Char* Test = Cast<AMC_Char>(FromChar);
		if (Test)
		{
			bool HasEmpty = false;

			if (!Test->FirstWeapon->IsValidLowLevel())
				HasEmpty = true;
			if (!Test->SecondWeapon->IsValidLowLevel() && !HasEmpty)
				HasEmpty = true;

			UMC_Weapon* MyTestWeapon = NewObject<UMC_Weapon>(FromChar,WeaponObject);
			MyTestWeapon->SetAmmo(PickUpAmmo);
			MyTestWeapon->SetBackAmmo(PickUpBackPackAmmo);
			MyTestWeapon->OnCreated(FromChar);

			if (HasEmpty)
			{
				if (Test->GetIsFirstWeapon())
					if (Test->FirstWeapon->IsValidLowLevel())
						Test->SecondWeapon = MyTestWeapon;
					else
						Test->FirstWeapon = MyTestWeapon;
				else
					if (Test->SecondWeapon->IsValidLowLevel())
						Test->FirstWeapon = MyTestWeapon;
					else
						Test->SecondWeapon = MyTestWeapon;
			}

			else
			{
				UMC_Weapon* CharWeapon;

				if (Test->GetIsFirstWeapon())
					CharWeapon = Test->FirstWeapon;
				else
					CharWeapon = Test->SecondWeapon;

				if (CharWeapon->IsValidLowLevel())
				{
					CharWeapon->SpawnPickUp(GetActorLocation());
					CharWeapon->OnDestroy();
				}

				if (Test->GetIsFirstWeapon())
					Test->FirstWeapon = MyTestWeapon;
				else
					Test->SecondWeapon = MyTestWeapon;
			}

			Destroy();
		}
	}
}

// Called every frame
void AWeaponPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

