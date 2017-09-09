// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "MC_Weapon.h"




bool UMC_Weapon::OnCreated(ACharPawn* CharRef)
{
	return false;

}


void UMC_Weapon::OnCreated_BNE_Implementation()
{
}

void UMC_Weapon::StartTrail_BNE_Implementation()
{}
void UMC_Weapon::EndTrail_BNE_Implementation()
{}

bool UMC_Weapon::FirstFire(APlayerController* InstigatorFF, FVector PointToShootFF, FRotator RotToShootFF)
{
	return false;
}

bool UMC_Weapon::SecondFire(APlayerController* InstigatorSF, FVector PointToShootSF, FRotator RotToShootSF)
{
	return false;
}


UWeaponSMC* UMC_Weapon::GetSMC()
{
	return SMC;
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

UAnimMontage* UMC_Weapon::GetAnimMontage(bool IsPrimeFire)
{
	if (IsPrimeFire)
	{
		return AnimMontageFF;
	}
	else
	{
		return AnimMontageSF;
	}
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

UAnimMontage* UMC_Weapon::GetReloadAnimMontage()
{
	return ReloadMontage;
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
	//if (TrailComponent->IsValidLowLevel())
	//{
	//TrailComponent->OnDestroy();
	//}

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

void UMC_Weapon::SetWeaponColor(FLinearColor NewColor)
{
	WeaponColor = NewColor;
}