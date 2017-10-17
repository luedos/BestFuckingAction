// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Projectails/DamageIntarface.h"
#include "CharPawn.generated.h"




UCLASS()
class DEMO_001_API ACharPawn : public ACharacter, public IDamageIntarface
{
	GENERATED_BODY()



public:
	// Sets default values for this character's properties
	ACharPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintPure, Category = Team)
	ETeamEnum GetTeam();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Damage)
		void DoDamage(float Damage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType);
	virtual void DoDamage_Implementation(float Damage, ETeamEnum DamageFromTeam, AActor* Couser, EDamageType DamageType) override;

	UFUNCTION(BlueprintCallable, Category = HP)
	void DamageHP(float Damage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = HP)
	void DeathStatus();

	UFUNCTION(BlueprintCallable, Category = Tests)
	bool TestForVisibilityOnActor(AActor* TestActor);

	UFUNCTION(BlueprintPure, Category = HP)
	bool GetIsDead();

	UFUNCTION(BlueprintCallable, Category = HP)
	void SetCanCharBeDamaged(bool NewStatus);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HP)
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HP)
	float MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Team)
	ETeamEnum Team;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HP)
		bool IsDead;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HP)
	bool bCanCharBeDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HP)
	FLinearColor CharColor;

};
