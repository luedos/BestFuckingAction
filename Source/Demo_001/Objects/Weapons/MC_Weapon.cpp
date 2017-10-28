// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "PickUps/WeaponPickUp.h"
#include "MC_Weapon.h"




bool UMC_Weapon::OnCreated(ACharPawn* CharRef)
{
	return false;

}



bool UMC_Weapon::FirstFire(APlayerController* InstigatorFF, FVector PointToShootFF, FRotator RotToShootFF)
{
	return false;
}

bool UMC_Weapon::SecondFire(APlayerController* InstigatorSF, FVector PointToShootSF, FRotator RotToShootSF)
{
	return false;
}

void UMC_Weapon::Reload()
{
	if (MaxAmmo != 0)
	{
		if ((MaxAmmo - Ammo) < BackPackAmmo)
		{
			BackPackAmmo -= (MaxAmmo - Ammo);
			Ammo = MaxAmmo;
		}
		else
		{
			Ammo += BackPackAmmo;
			BackPackAmmo = 0;
		}
	}
}



void UMC_Weapon::AddAmmo(int AmmoToAdd)
{
	BackPackAmmo += AmmoToAdd;
	if (BackPackAmmo > MaxBackPackAmmo)
	{
		BackPackAmmo = MaxBackPackAmmo;
	}
}

void UMC_Weapon::SetAmmo(int AmmoToSet)
{
	if (AmmoToSet > MaxAmmo)
		Ammo = MaxAmmo;
	else
		Ammo = AmmoToSet;
}

void UMC_Weapon::SetBackAmmo(int AmmoToSet)
{
	if (AmmoToSet > MaxBackPackAmmo)
		BackPackAmmo = MaxBackPackAmmo;
	else
		BackPackAmmo = AmmoToSet;
}

ACharacter * UMC_Weapon::GetChar()
{
	return Char;
}

int UMC_Weapon::GetAmmo()
{
	return Ammo;
}

int UMC_Weapon::GetMaxAmmo()
{
	return MaxAmmo;
}

int UMC_Weapon::GetBackPackAmmo()
{
	return BackPackAmmo;
}

int UMC_Weapon::GetMaxBackPackAmmo()
{
	return MaxBackPackAmmo;
}

bool UMC_Weapon::GetIsFA()
{
	return bIsFirstAutomatic;
}

bool UMC_Weapon::GetIsSA()
{
	return bIsSecondAutomatic;
}

float UMC_Weapon::GetFirstFireRate()
{
	return FirstFireRate;
}
float UMC_Weapon::GetSecondFireRate()
{
	return SecondFireRate;
}

FName UMC_Weapon::GetName()
{
	return NameOfTheGun;
}

UParticleSystem* UMC_Weapon::GetFireParticle(bool IsPrimeFire)
{
	if (IsPrimeFire)
	{
		return FireParticleFF;
	}
	else
	{
		return FireParticleSF;
	}
}

float UMC_Weapon::GetReloadRate()
{
	return ReloadRate;
}

bool UMC_Weapon::GetShotGunStyle()
{
	return ShotgunStyle;
}

UParticleSystem * UMC_Weapon::GetReloadParticle()
{
	return ReloadParticle;
}


void UMC_Weapon::OnDestroy()
{

	if (SMC->IsValidLowLevel())
	{
		SMC->OnDestroy();
	}

	if (ParticlesArray.Num() != 0)
	{
		for (int i = 0; i < ParticlesArray.Num(); i++)
		{
			if (ParticlesArray[i]->IsValidLowLevel())
			{
				ParticlesArray[i]->DestroyComponent();
			}
		}
	}

	MarkPendingKill();
}


void UMC_Weapon::SpawnPickUp(FVector Location)
{
	if (MyWeaponPickUp->IsValidLowLevel())
	{


		if (Char->IsValidLowLevel())
		{
			UWorld* World = Char->GetWorld();
			if (World != NULL)
			{

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = Char;
				SpawnParams.Instigator = Char;
				
				APickUp* TestPickUp = World->SpawnActor<APickUp>(MyWeaponPickUp, FTransform(FRotator(0, 0, 0), Location, FVector(0, 0, 0)),SpawnParams);
				
				AWeaponPickUp* MyPickUp = Cast<AWeaponPickUp>(TestPickUp);
				if (MyPickUp)
				{
					MyPickUp->PickUpAmmo = Ammo;
					MyPickUp->PickUpBackPackAmmo = BackPackAmmo;
				}

				
			}
		}
	}

}