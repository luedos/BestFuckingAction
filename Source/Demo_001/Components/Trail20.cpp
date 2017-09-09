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
	//Проверка на мир
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//Проверка на правильность введенных данных
		if (SMCReference->IsValidLowLevel() && TrailMaterial->IsValidLowLevel() && NumOfTrailMeshes != 0 && TrailTimeLength > 0.1)
		{
			//В случае если макс. число запасных компонентов не указано, оно ставится по умолчанию
			if (MaxNumOfBackSMC < 3)
			{
				MinNumOfBackSMC = 3;
			}
			//заданние мин. числа запасных компонентов
			MinNumOfBackSMC = MaxNumOfBackSMC*0.6;

			//Указание оригинального компонента
			SMC = SMCReference;

			//Создание первых запасных компонентов
			CreateMeshComponent();


			//Проверка на активность цикла
			if (!World->GetTimerManager().IsTimerActive(TrailTimer))
			{
				//Указание первого промежутка времени и запуск цикла
				DeleteDelay = TrailTimeLength / NumOfTrailMeshes;
				World->GetTimerManager().SetTimer(TrailTimer, this, &UTrail20::TrailCicle, DeleteDelay);
			}

			//В случае если указано время смерти хвоста запускается таймер
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
	//Проверка на мир
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//Цикл заполняющий массив запасных компонентов до максимума
		for (int i = 0; BackSMCsArray.Num() < MaxNumOfBackSMC; i++)
		{
			//Создание и регестрация компонента
			LastSMC = NewObject<UStaticMeshComponent>(GetOwner());
			LastSMC->OnComponentCreated();
			LastSMC->RegisterComponent();

			//Задание положения компонента в мире
			if (SMCsArray.Num() != 0)
			{
				FTransform MeshTransform = UKismetMathLibrary::SelectTransform(SMCsArray.Last()->GetComponentTransform(), SMC->GetComponentTransform(), SMCsArray.Last()->IsValidLowLevel());
				LastSMC->SetWorldTransform(UKismetMathLibrary::TLerp(MeshTransform, SMC->GetComponentTransform(), 0.5f));
			}
			else
			{
				LastSMC->SetWorldTransform(SMC->GetComponentTransform());
			}



			//Скрытие компонента из виду
			LastSMC->SetVisibility(false);

			//Задание меша и материала компонента
			LastSMC->SetStaticMesh(SMC->StaticMesh);
			LastSMC->SetMaterial(0, TrailMaterial);

			//Прикрепление компонента к оригинальному
			LastSMC->AttachTo(SMC);

			//Добавление компонента в массив запасных компонентов
			BackSMCsArray.Add(LastSMC);
		}
	}
}

//Удаление компонента (из массива первостепенных компонентов)
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
	//Проверка на мир
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//Перевод компонента из запасных в основные
		TransferSMC();
		//Добавление времени перехода в массив
		DeleteDelayArray.Add(DeleteDelay);
		//В случае если количество запасных компонентов меньше миннимального они пополняются
		if (BackSMCsArray.Num() <= MinNumOfBackSMC)
		{
			if (World->GetTimerManager().IsTimerActive(CreateSMCTimer))
			{
				World->GetTimerManager().SetTimer(CreateSMCTimer, this, &UTrail20::CreateMeshComponent, 0.f);
			}
			
		}
		//Определение времени перехода и запуск таймера цикла
		DeleteDelay = TrailTimeLength / NumOfTrailMeshes;
		World->GetTimerManager().SetTimer(TrailTimer, this, &UTrail20::TrailCicle, DeleteDelay);


		//Если количество основных компонентов больше чем необходимо, лишние удаляются
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
	//Проверка на мир
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//Проверка на дибила
		if (SMCsArray.Num() != 0)
		{
			//Удаление компонента
			DestroyMeshComponent();
			//Запуск таймера цикла удаления компонента
			if (SMCsArray.Num() != 0)
			{
				World->GetTimerManager().SetTimer(DestroyTimer, this, &UTrail20::DeleteCicle, DeleteDelayArray[0]);
			}
		}
	}
}

void UTrail20::FinishTrail()
{
	//Проверка на мир
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		//Очистка массива запасных компонентов
		for (int i = 0; i < BackSMCsArray.Num(); i++)
		{
			if (BackSMCsArray[i]->IsValidLowLevel())
			{
				BackSMCsArray[i]->DestroyComponent();
			}
		}
		BackSMCsArray.Empty();

		//Запуск цикла удаления компонентов
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




//Чистка всех массивов и таймеров
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

//Перевод компонента из запасных в основные
void UTrail20::TransferSMC()
{
	//Проверка на мир
	UWorld* World = GetOwner()->GetWorld();
	if (World != NULL)
	{
		if (BackSMCsArray.Num() != 0)
		{
			if (BackSMCsArray[0]->IsValidLowLevel())
			{
				//Задание болванчика
				UStaticMeshComponent* LocalSMC = BackSMCsArray[0];



				//Добавление компонента в основной массив
				SMCsArray.Add(LocalSMC);

				//Отсоиденение компонента от оригенального
				LocalSMC->DetachFromParent();

				//Задание положения компонента в мире
				if (SMCsArray.Num() != 0)
				{
					FTransform MeshTransform = UKismetMathLibrary::SelectTransform(SMCsArray.Last()->GetComponentTransform(), SMC->GetComponentTransform(), SMCsArray.Last()->IsValidLowLevel());
					LocalSMC->SetWorldTransform(UKismetMathLibrary::TLerp(MeshTransform, SMC->GetComponentTransform(), 0.5f));
				}
				else
				{
					LocalSMC->SetWorldTransform(SMC->GetComponentTransform());
				}



				//Выключение невидимости компонента
				LocalSMC->SetVisibility(true);

				//Удаление компонента из массива запасных
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