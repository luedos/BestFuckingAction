// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineMinimal.h"
#include "Engine.h"
#include "GameHUD.h"

AGameHUD::AGameHUD()
{
	CrossHairWidth = 0.f;
	ASMC_Char = false;
}



void AGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCustomCrossHair();
}


void AGameHUD::DrawCustomCrossHair()
{

	UWorld* World = GetWorld();
	if (World != NULL)
	{


		APlayerController* PController = UGameplayStatics::GetPlayerController(World, 0);

		if (PController->IsValidLowLevel())
		{
			if (!PController->bShowMouseCursor)
			{
				int VSizeX = 0;
				int VSizeY = 0;

				PController->GetViewportSize(VSizeX, VSizeY);

				float PositionX = UKismetMathLibrary::Conv_IntToFloat(Canvas->SizeX - VSizeX);
				float PositionY = UKismetMathLibrary::Conv_IntToFloat(Canvas->SizeY - VSizeY);

				float MousePosX;
				float MousePosY;
				PController->GetMousePosition(MousePosX, MousePosY);

				PositionX = PositionX / 2 + MousePosX - CrossHairWidth / 2;
				PositionY = PositionY / 2 + MousePosY - CrossHairWidth / 2;


				DrawMaterial(CrossHairMaterial, PositionX, PositionY, CrossHairWidth, CrossHairWidth, 0, 0, 1, 1);
			}
			else
				if (ASMC_Char)
				{
					int VSizeX = 0;
					int VSizeY = 0;

					PController->GetViewportSize(VSizeX, VSizeY);

					float PositionX = UKismetMathLibrary::Conv_IntToFloat(Canvas->SizeX - VSizeX);
					float PositionY = UKismetMathLibrary::Conv_IntToFloat(Canvas->SizeY - VSizeY);

					float MousePosX;
					float MousePosY;
					PController->GetMousePosition(MousePosX, MousePosY);

					PositionX = PositionX / 2 + MousePosX - CrossHairWidth / 2;
					PositionY = PositionY / 2 + MousePosY - CrossHairWidth / 2;


					DrawMaterial(CrossHairMaterial, PositionX, PositionY, CrossHairWidth, CrossHairWidth, 0, 0, 1, 1);
				}
		}
	}
}