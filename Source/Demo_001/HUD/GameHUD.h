// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_001_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	

		virtual void DrawHUD() override;

public:

	AGameHUD();
	
protected:

	UFUNCTION(BlueprintCallable, Category = CustomHUD)
		void DrawCustomCrossHair();

	UPROPERTY(EditAnywhere, Category = CustomHUD)
	UMaterial* CrossHairMaterial;

	UPROPERTY(EditAnywhere, Category = CustomHUD)
	float CrossHairWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomHUD)
	bool ASMC_Char;

};
