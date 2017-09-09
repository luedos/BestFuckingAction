// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Enemy_Char.h"
#include "Components/Shield.h"

#include "Enemy_WIcoSphere.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API AEnemy_WIcoSphere : public AEnemy_Char
{
	GENERATED_BODY()

		public:

		AEnemy_WIcoSphere();
	
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FaceArrow, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* ComponentsFaceArrow;

		UFUNCTION(BlueprintCallable, Category = Shield)
		void ShieldUp(float InDelay);

		UFUNCTION(BlueprintCallable, Category = Shield)
		void ShieldDown();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shield)
		TSubclassOf<UShield> UsingShield;

		UFUNCTION(BlueprintCallable, Category = FaceArrow)
		bool InterpFaceArrow(float TimeDelay, FVector ToPoint);

		UFUNCTION(BlueprintCallable, Category = FaceArrow)
		void ChangeArrowInterpSpeed(float NewSpeed);

protected:

	UPROPERTY(BlueprintReadOnly, Category = Shield)
	UShield* ShieldComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FaceArrow)
	float ArrowInterpSpeed;

private:

	FTimerHandle ShieldTimer;


};
