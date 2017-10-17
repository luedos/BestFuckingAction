// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Character/CharPawn.h"
#include "ParticleDefinitions.h"
#include "Components/Shield.h"
#include "Projectails/DamageIntarface.h"
#include "Components/KritComponent.h"
#include "Components/WeaponSMC.h"
#include "MC_Weapon.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DEMO_001_API UMC_Weapon : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Statistic)
	virtual bool OnCreated(ACharPawn* CharRef);

	UFUNCTION(BlueprintImplementableEvent, Category = Statistic)
	void OnCreated_BNE();


	UFUNCTION(BlueprintCallable, Category = Fire)
	virtual bool FirstFire(APlayerController* InstigatorF, FVector PointToShootF, FRotator RotToShootF);

	UFUNCTION(BlueprintCallable, Category = Fire)
	virtual bool SecondFire(APlayerController* InstigatorS, FVector PointToShootS, FRotator RotToShootS);
	
	UFUNCTION(BlueprintCallable, Category = Ammo)
	void Reload();
	
	UFUNCTION(BlueprintCallable, Category = Ammo)
	void AddAmmo(int AmmoToAdd);

	UFUNCTION(BlueprintPure, Category = Statistic)
	ACharacter* GetChar();
	UFUNCTION(BlueprintPure, Category = Ammo)
	int GetAmmo();
	UFUNCTION(BlueprintPure, Category = Ammo)
	int GetMaxAmmo();
	UFUNCTION(BlueprintPure, Category = Ammo)
	int GetBackPackAmmo();
	UFUNCTION(BlueprintPure, Category = Ammo)
	int GetMaxBackPackAmmo();
	UFUNCTION(BlueprintPure, Category = Fire)
	bool GetIsFA();
	UFUNCTION(BlueprintPure, Category = Fire)
	bool GetIsSA();
	UFUNCTION(BlueprintPure, Category = Fire)
	float GetFirstFireRate();
	UFUNCTION(BlueprintPure, Category = Fire)
	float GetSecondFireRate();
	UFUNCTION(BlueprintPure, Category = Fire)
	FName GetName();
	UFUNCTION(BlueprintPure, Category = Visualisation)
	UParticleSystem* GetFireParticle(bool IsPrimeFire);
	UFUNCTION(BlueprintPure, Category = Visualisation)
	float GetReloadRate();
	UFUNCTION(BlueprintPure, Category = Visualisation)
	bool GetShotGunStyle();

	UFUNCTION(BlueprintPure, Category = Visualisation)
	UParticleSystem* GetReloadParticle();

	UFUNCTION(BlueprintCallable, Category = Visualisation)
		UWeaponSMC* GetSMC() { return SMC; }

	UFUNCTION(BlueprintCallable, Category = Destroy)
		void OnDestroy();

	UFUNCTION(BlueprintCallable, Category = Visualisation)
	void SetWeaponColor(FLinearColor NewColor) { WeaponColor = NewColor; }

protected:


	//���������� �������������� ����� ��� ���
	UPROPERTY(EditAnywhere, Category = Fire)
	bool bIsFirstAutomatic;
	UPROPERTY(EditAnywhere, Category = Fire)
	bool bIsSecondAutomatic;

	//������ ���������� ��������� ��������
	UPROPERTY(EditAnywhere, Category = Ammo)
	int Ammo;
	UPROPERTY(EditAnywhere, Category = Ammo)
	int MaxAmmo;
	UPROPERTY(EditAnywhere, Category = Ammo)
	int BackPackAmmo;
	UPROPERTY(EditAnywhere, Category = Ammo)
	int MaxBackPackAmmo;

	//������ ���������� ���������� �������� ��������
	UPROPERTY(EditAnywhere, Category = Fire)
	float FirstFireRate;
	UPROPERTY(EditAnywhere, Category = Fire)
	float SecondFireRate;

	//������ ���������� ��������� � ��������������
	UPROPERTY(EditAnywhere, Category = Statistic)
	FName NameOfTheGun;

	ACharPawn* Char;



	//------------------------
	UPROPERTY(EditAnywhere, Category = Visualisation)
	UParticleSystem* FireParticleFF;
	UPROPERTY(EditAnywhere, Category = Visualisation)
	UParticleSystem* FireParticleSF;
	UPROPERTY(EditAnywhere, Category = Visualisation)
	bool IsSMC;
	UPROPERTY(EditAnywhere, Category = Visualisation)
	UParticleSystem* ReloadParticle;
	//------------------------

	UPROPERTY(EditAnywhere, Category = Visualisation)
	float ReloadRate;
	UPROPERTY(EditAnywhere, Category = Visualisation)
	bool ShotgunStyle;

	UPROPERTY(EditAnywhere, Category = Visualisation)
	UStaticMesh* GunMesh;
	UPROPERTY(EditAnywhere, Category = Visualisation)
	UStaticMesh* ShapeMesh;

	UPROPERTY(EditAnywhere, Category = Visualisation)
	USoundBase* FFSound_Fire;
	UPROPERTY(EditAnywhere, Category = Visualisation)
	USoundBase* SFSound_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visualisation)
	UParticleSystem* TrailParticle;
	UPROPERTY(EditAnywhere, Category = Visualisation)
	UMaterial* MeshMat;

	UPROPERTY(EditAnywhere, Category = Visualisation)
	FLinearColor StartTrailColor;

	UPROPERTY(EditAnywhere, Category = Visualisation)
	FLinearColor EndTrailColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Visualisation)
	FLinearColor WeaponColor;

	//���������� ����������� ��� ����
	UPROPERTY(EditAnywhere, Category = Visualisation)
	TSubclassOf<UWeaponSMC> WeaponSMCRef;

	UWeaponSMC* SMC;

	UPROPERTY(BlueprintReadWrite, Category = Visualisation)
	TArray<UParticleSystemComponent*> ParticlesArray;

};
