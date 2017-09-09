// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"
#include "Trail20.h"


// Sets default values for this component's properties
UTrail20::UTrail20()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTrail20::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTrail20::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTrail20::StartTrail(float TrailLength, UStaticMeshComponent* SMCReference)
{
	//�������� �� ���
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//�������� �� ������������ ��������� ������
		if (SMCReference->IsValidLowLevel() && TrailMaterial->IsValidLowLevel() && NumOfTrailMeshes != 0 && TrailTimeLength > 0.1)
		{
			//� ������ ���� ����. ����� �������� ����������� �� �������, ��� �������� �� ���������
			if (MaxNumOfBackSMC < 3)
			{
				MinNumOfBackSMC = 3;
			}
			//�������� ���. ����� �������� �����������
			MinNumOfBackSMC = MaxNumOfBackSMC*0.6;

			//�������� ������������� ����������
			SMC = SMCReference;

			//�������� ������ �������� �����������
			CreateMeshComponent();


			//�������� �� ���������� �����
			if (!World->GetTimerManager().IsTimerActive(TrailTimer))
			{
				//�������� ������� ���������� ������� � ������ �����
				DeleteDelay = TrailTimeLength / NumOfTrailMeshes;
				World->GetTimerManager().SetTimer(TrailTimer, this, &UTrail20::TrailCicle, DeleteDelay);
			}

			//� ������ ���� ������� ����� ������ ������ ����������� ������
			if (TrailLength > 0.1f)
			{
				World->GetTimerManager().SetTimer(FinishTrailTimer, this, &UTrail20::FinishTrail, TrailLength);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Trail can't be created becouse of inright input!"));
		}

	}
}

void UTrail20::CreateMeshComponent()
{
	//�������� �� ���
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//���� ����������� ������ �������� ����������� �� ���������
		for (int i = 0; BackSMCsArray.Num() < MaxNumOfBackSMC; i++)
		{
			//�������� � ����������� ����������
			LastSMC = NewObject<UStaticMeshComponent>(GetOwner());
			LastSMC->OnComponentCreated();
			LastSMC->RegisterComponent();

			//������� ��������� ���������� � ����
			if (SMCsArray.Num() != 0)
			{
				FTransform MeshTransform = UKismetMathLibrary::SelectTransform(SMCsArray.Last()->GetComponentTransform(), SMC->GetComponentTransform(), SMCsArray.Last()->IsValidLowLevel());
				LastSMC->SetWorldTransform(UKismetMathLibrary::TLerp(MeshTransform, SMC->GetComponentTransform(), 0.5f));
			}
			else
			{
				LastSMC->SetWorldTransform(SMC->GetComponentTransform());
			}



			//������� ���������� �� ����
			LastSMC->SetVisibility(false);

			//������� ���� � ��������� ����������
			LastSMC->SetStaticMesh(SMC->StaticMesh);
			LastSMC->SetMaterial(0, TrailMaterial);

			//������������ ���������� � �������������
			LastSMC->AttachTo(SMC);

			//���������� ���������� � ������ �������� �����������
			BackSMCsArray.Add(LastSMC);
		}
	}
}

//�������� ���������� (�� ������� �������������� �����������)
void UTrail20::DestroyMeshComponent()
{
	if (SMCsArray[0]->IsValidLowLevel())
	{
		SMCsArray[0]->DestroyComponent();
	}
	SMCsArray.RemoveAt(0);
	DeleteDelayArray.RemoveAt(0);
}



void UTrail20::TrailCicle()
{
	//�������� �� ���
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//������� ���������� �� �������� � ��������
		TransferSMC();
		//���������� ������� �������� � ������
		DeleteDelayArray.Add(DeleteDelay);
		//� ������ ���� ���������� �������� ����������� ������ ������������� ��� �����������
		if (BackSMCsArray.Num() <= MinNumOfBackSMC)
		{
			if (World->GetTimerManager().IsTimerActive(CreateSMCTimer))
			{
				World->GetTimerManager().SetTimer(CreateSMCTimer, this, &UTrail20::CreateMeshComponent, 0.f);
			}
			
		}
		//����������� ������� �������� � ������ ������� �����
		DeleteDelay = TrailTimeLength / NumOfTrailMeshes;
		World->GetTimerManager().SetTimer(TrailTimer, this, &UTrail20::TrailCicle, DeleteDelay);


		//���� ���������� �������� ����������� ������ ��� ����������, ������ ���������
		if (SMCsArray.Num() >= NumOfTrailMeshes)
		{
			if (SMCsArray.Num() == NumOfTrailMeshes)
			{
				DestroyMeshComponent();
			}

			if (SMCsArray.Num() > NumOfTrailMeshes)
			{
				while (SMCsArray.Num() > NumOfTrailMeshes)
				{
					DestroyMeshComponent();
				}
			}
		}

	}
}

void UTrail20::DeleteCicle()
{
	//�������� �� ���
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//�������� �� ������
		if (SMCsArray.Num() != 0)
		{
			//�������� ����������
			DestroyMeshComponent();
			//������ ������� ����� �������� ����������
			if (SMCsArray.Num() != 0)
			{
				World->GetTimerManager().SetTimer(DestroyTimer, this, &UTrail20::DeleteCicle, DeleteDelayArray[0]);
			}
		}
	}
}

void UTrail20::FinishTrail()
{
	//�������� �� ���
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//������� ������� �������� �����������
		for (int i = 0; i < BackSMCsArray.Num(); i++)
		{
			if (BackSMCsArray[i]->IsValidLowLevel())
			{
				BackSMCsArray[i]->DestroyComponent();
			}
		}
		BackSMCsArray.Empty();

		//������ ����� �������� �����������
		if (World->GetTimerManager().IsTimerActive(TrailTimer))
		{
			GetOwner()->GetWorld()->GetTimerManager().ClearTimer(TrailTimer);
		}
		if (DeleteDelayArray.Num() != 0)
		{
			World->GetTimerManager().SetTimer(DestroyTimer, this, &UTrail20::DeleteCicle, DeleteDelayArray[0]);
		}
	}
}

int UTrail20::TestFunction(UStaticMeshComponent* SMCTestReference)
{
	SMC = SMCTestReference;


	CreateMeshComponent();
	
	return BackSMCsArray.Num();
}




//������ ���� �������� � ��������
void UTrail20::ClearAllTrail()
{
	UWorld* World = GetOwner()->GetWorld();
	for (int i = 0; i < SMCsArray.Num(); i++)
	{
		if (SMCsArray[i]->IsValidLowLevel())
		{
			SMCsArray[i]->DestroyComponent();
		}
	}
	for (int i = 0; i < BackSMCsArray.Num(); i++)
	{
		if (BackSMCsArray[i]->IsValidLowLevel())
		{
			BackSMCsArray[i]->DestroyComponent();
		}
	}
	SMCsArray.Empty();
	BackSMCsArray.Empty();
	DeleteDelayArray.Empty();
	if (World != NULL)
	{
		World->GetTimerManager().ClearTimer(TrailTimer);
		World->GetTimerManager().ClearTimer(FinishTrailTimer);
		World->GetTimerManager().ClearTimer(DestroyTimer);
	}


}

//������� ���������� �� �������� � ��������
void UTrail20::TransferSMC()
{
	//�������� �� ���
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		if (BackSMCsArray.Num() != 0)
		{
			if (BackSMCsArray[0]->IsValidLowLevel())
			{
				//������� ����������
				UStaticMeshComponent* LocalSMC = BackSMCsArray[0];



				//���������� ���������� � �������� ������
				SMCsArray.Add(LocalSMC);

				//������������ ���������� �� �������������
				LocalSMC->DetachFromParent();

				//������� ��������� ���������� � ����
				if (SMCsArray.Num() != 0)
				{
					FTransform MeshTransform = UKismetMathLibrary::SelectTransform(SMCsArray.Last()->GetComponentTransform(), SMC->GetComponentTransform(), SMCsArray.Last()->IsValidLowLevel());
					LocalSMC->SetWorldTransform(UKismetMathLibrary::TLerp(MeshTransform, SMC->GetComponentTransform(), 0.5f));
				}
				else
				{
					LocalSMC->SetWorldTransform(SMC->GetComponentTransform());
				}



				//���������� ����������� ����������
				LocalSMC->SetVisibility(true);

				//�������� ���������� �� ������� ��������
				BackSMCsArray.RemoveAt(0);
			}
		}
	}
}

TArray<UStaticMeshComponent*> UTrail20::GetMeshArray()
{
	return SMCsArray;
}

TArray<UStaticMeshComponent*> UTrail20::GetBackMeshArray()
{
	return BackSMCsArray;
}

TArray<float> UTrail20::GetDelayArray()
{
	return DeleteDelayArray;
}