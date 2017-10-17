// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Projectails/DamageIntarface.h"
#include "Character/CharPawn.h"
#include "KritComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DEMO_001_API UKritComponent : public UStaticMeshComponent, public IDamageIntarface
{
	GENERATED_BODY()
	
public:

	UKritComponent();

	UFUNCTION(BlueprintCallable, Category = Krit)
	void OnKrit(float InDamage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType);



	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Krit)
	void OnKrit_BNE(float InDamage_BNE, ETeamEnum DamageFromTeam, AActor* Couser_BNE, EDamageType DamageType_BNE);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Damage)
		void DoDamage(float Damage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType);
	virtual void DoDamage_Implementation(float Damage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType) override;

	UFUNCTION(BlueprintCallable, Category = OnCreated)
	void OnCreatedKC(ACharPawn* CharRef);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Char)
	ACharPawn* Char;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Krit)
	float KritMultiplier;

};
