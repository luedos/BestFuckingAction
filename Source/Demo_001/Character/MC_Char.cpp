// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo_001.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Character/Enemy_Char.h"
#include "Engine.h"
#include "Objects/CharSkills/Object_Skills.h"
#include "Objects/CharSkills/Object_Skills_NormalDesh.h"
#include "Objects/Weapons/MC_Weapon.h"
#include "GameFramework/PlayerInput.h"
#include "MC_Char.h"



// Sets default values
AMC_Char::AMC_Char()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a Camera Rotation Arrow
	CameraRotationArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraRotationArrowComponent"));
	CameraRotationArrow->SetupAttachment(RootComponent);

	// Create a CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(CameraRotationArrow);
	CameraBoom->TargetArmLength = 1000.0f; // The camera follows at this distance behind the character	
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0, 0));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CameraInterpSpeed = 10.f;
	CameraInterpLerpAlfa = 0.4f;

	Desh = CreateDefaultSubobject<UObject_Skills_NormalDesh>(TEXT("Skill to Desh"));

	

	IsRotateCamera = false;
	CanPrimeFire = true;
	CanAlternativeFire = true;
	IsFirstWeapon = false;

	IsRotateCharMesh = true;

	HP = 500.f;
	MaxHP = 500.f;

	bCanMove = true;

	Team = ETeamEnum::TE_Player;

	DirectionVector = FVector(0,0,0);

	DirectionValue = 0;

	ForwardMoveValue = 0;

	RightMoveValue = 0;

	InterpWalkSpeedVector = 7.f;
	
	InterpWalkSpeedValue = 7.f;

	PercentOfValue = 0.7f;



	DeshLength = 800.f;
	DeshTime = 0.15f;
	NumberOfSmallDeshes = 40;
	CountOfSmallDeshes = 0;

	ASinConst = 15.f;
	BSinConst = 15.f;
	SinHight = 1000.f;
	StartDeshSpeed = 100.f;
	ArraySum = 0;
	Coefficient = 0;

	DeshEnemyDelay = 0.5;
}

// Called when the game starts or when spawned
void AMC_Char::BeginPlay()
{
	Super::BeginPlay();
	ChangeWeapon();
	//GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

// Called every frame
void AMC_Char::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	InterpCamera(DeltaTime);
	if (bCanMove)
	{
		InterpWalk(DeltaTime);
	}
}

// Called to bind functionality to input
void AMC_Char::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);

	InputComp->BindAction("Desh", IE_Pressed, this, &AMC_Char::UseDesh);

	InputComp->BindAction("PrimeFire", IE_Pressed, this, &AMC_Char::PrimeFire);
	InputComp->BindAction("AlternativeFire", IE_Pressed, this, &AMC_Char::AlternativeFire);

	InputComp->BindAction("Reload", IE_Pressed, this, &AMC_Char::StartReload);
	
	InputComp->BindAction("ChangeWeapon", IE_Pressed, this, &AMC_Char::StartChangeWeapon);

	InputComp->BindAxis("MoveForward", this, &AMC_Char::MoveForward);
	InputComp->BindAxis("MoveRight", this, &AMC_Char::MoveRight);
}

void AMC_Char::WalkFunction(FVector DirectionVector, float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AddMovementInput(DirectionVector, Value);
	}
	
}

void AMC_Char::InterpWalk(float DeltaTimeWalkInterp)
{
	FVector TestVector = FVector(0, 0, 0);
	float TestValue = 0;

	if (ForwardMoveValue != 0 || RightMoveValue != 0)
	{
		TestValue = 1;
	}

	TestVector = TestVector + CameraRotationArrow->GetForwardVector() * ForwardMoveValue;
	TestVector = TestVector + CameraRotationArrow->GetRightVector() * RightMoveValue;

	DirectionVector = UKismetMathLibrary::VInterpTo(DirectionVector, TestVector, DeltaTimeWalkInterp, InterpWalkSpeedVector * (1.f + (TestValue - 1) * PercentOfValue));

	DirectionValue = UKismetMathLibrary::FInterpTo(DirectionValue, TestValue, DeltaTimeWalkInterp, InterpWalkSpeedValue * (1.f + (TestValue - 1) * PercentOfValue));

	WalkFunction(DirectionVector, DirectionValue);

}

void AMC_Char::InterpCamera(float DeltaSeconds)
{
	if (!IsRotateCamera)
	{
		FHitResult HitResUnderCursor;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECC_Visibility, false, HitResUnderCursor);
		HitResUnderCursor.Location.Z = GetActorLocation().Z;
		CharLookPoint = HitResUnderCursor.Location;
		FVector PointToInterp = UKismetMathLibrary::VLerp(GetActorLocation(), HitResUnderCursor.Location, CameraInterpLerpAlfa);
		CameraRotationArrow->SetWorldLocation(UKismetMathLibrary::VInterpTo(CameraRotationArrow->GetComponentLocation(), PointToInterp, DeltaSeconds, CameraInterpSpeed));
		CameraBoom->SetWorldLocation(CameraRotationArrow->GetComponentLocation());

		FRotator RotateMesh = FRotator(0, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResUnderCursor.Location).Yaw - 90.f, 0);
	
		if (IsRotateCharMesh)
		{
			GetMesh()->SetWorldRotation(RotateMesh);
		}

		CharRotation = FRotator(0, RotateMesh.Yaw + 90.f, 0);


	}
}




FRotator AMC_Char::GetCharRotation()
{
	return CharRotation;
}

FVector AMC_Char::GetCharLookPoint()
{
	return CharLookPoint;
}

float AMC_Char::TestFunction(float TestRef)
{
	return UKismetMathLibrary::Sin(TestRef);
}

bool AMC_Char::GetIsFirstWeapon()
{
	return IsFirstWeapon;
}

void AMC_Char::ChangeWeapon()
{
	
	if (UKismetMathLibrary::SelectObject(FirstWeapon, SecondWeapon, !IsFirstWeapon)->IsValidLowLevel())
	{
		if (IsFirstWeapon)
		{
			FirstWeapon->EndTrail_BNE();
			SecondWeapon->StartTrail_BNE();
		}
		else
		{
			FirstWeapon->StartTrail_BNE();
			SecondWeapon->EndTrail_BNE();
		}
		
		IsFirstWeapon = !IsFirstWeapon;
		ChangeWeapon_BNE();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Weapon is absent"));
	}
}

void AMC_Char::ChangeWeapon_BNE_Implementation()
{}

void AMC_Char::StartChangeWeapon()
{
	StopReloading();
	if (UKismetMathLibrary::SelectObject(FirstWeapon, SecondWeapon, !IsFirstWeapon)->IsValidLowLevel() && !GetWorldTimerManager().IsTimerActive(ChangeWeaponTimer))
	{
		GetWorldTimerManager().SetTimer(ChangeWeaponTimer, this, &AMC_Char::ChangeWeapon, 0.5f);
		StartChangeWeapon_BNE();
	}
}

void AMC_Char::StartChangeWeapon_BNE_Implementation()
{}

void AMC_Char::StopChangeWeapon()
{
	GetWorldTimerManager().ClearTimer(ChangeWeaponTimer);
	StopChangeWeapon_BNE();
}

void AMC_Char::StopChangeWeapon_BNE_Implementation()
{}

void AMC_Char::StartReload_BNE_Implementation()
{}

void AMC_Char::StartReload()
{

	if(!GetWorldTimerManager().IsTimerActive(ReloadTimer) && !GetWorldTimerManager().IsTimerActive(ChangeWeaponTimer))
	{ 

		if (IsFirstWeapon)
		{

			if (FirstWeapon->IsValidLowLevel())
			{


				if (FirstWeapon->GetBackPackAmmo() > 0 && FirstWeapon->GetAmmo() < FirstWeapon->GetMaxAmmo())
				{
					StartReload_BNE();
					IsReload = true;
					GetWorldTimerManager().SetTimer(ReloadTimer, this, &AMC_Char::ReloadWeapon, FirstWeapon->GetReloadRate());

				}
			}
		}
		else
		{
			if (SecondWeapon->IsValidLowLevel() && SecondWeapon->GetAmmo() < SecondWeapon->GetMaxAmmo())
			{
				if (SecondWeapon->GetBackPackAmmo() > 0)
				{
					StartReload_BNE();
					IsReload = true;
					GetWorldTimerManager().SetTimer(ReloadTimer, this, &AMC_Char::ReloadWeapon, SecondWeapon->GetReloadRate());
				}
			}
		}
	}

}

void AMC_Char::ReloadWeapon()
{

	if (IsFirstWeapon)
	{
		if (FirstWeapon->IsValidLowLevel())
			FirstWeapon->Reload();
	}
	else
	{
		if (SecondWeapon->IsValidLowLevel())
			SecondWeapon->Reload();
	}
	IsReload = false;
}

void AMC_Char::StopReloading_BNE_Implementation()
{}

void AMC_Char::StopReloading()
{
	StopReloading_BNE();
	GetWorldTimerManager().ClearTimer(ReloadTimer);
	IsReload = false;
}

bool AMC_Char::GetIsReload()
{
	return IsReload;
}

void AMC_Char::MoveForward(float Value)
{
	//if ((Controller != NULL) && (Value != 0.0f))
	//{
	//	AddMovementInput(CameraRotationArrow->GetForwardVector(), Value);
	//}

	ForwardMoveValue = Value;
}

void AMC_Char::MoveRight(float Value)
{
	//if ((Controller != NULL) && (Value != 0.0f))
	//{
	//	AddMovementInput(CameraRotationArrow->GetRightVector(), Value);
	//}

	RightMoveValue = Value;
}





void AMC_Char::FireBNE_Implementation(UMC_Weapon * Weapon, bool IsPrimeFire, bool FireOrMisfire)
{
}

void AMC_Char::UseDesh()
{
	
	FVector TestVector = FVector(0, 0, 0);
	float TestValue = 0;

	if (ForwardMoveValue != 0 || RightMoveValue != 0)
	{
		TestValue = 1;
	}

	TestVector = TestVector + CameraRotationArrow->GetForwardVector() * ForwardMoveValue;
	TestVector = TestVector + CameraRotationArrow->GetRightVector() * RightMoveValue;

	Desh_Event_Implementation(TestVector);

	StartDesh(TestVector);

	//Desh->UseSkill_Implementation(this, 10000.f, 1000.f, TestVector);


}






void AMC_Char::PrimeFire()
{

	if (UKismetMathLibrary::SelectObject(FirstWeapon, SecondWeapon, IsFirstWeapon)->IsValidLowLevel())
	{
		if (CanPrimeFire)
		{
			if (IsFirstWeapon)
			{
				if (FirstWeapon->GetShotGunStyle() || !IsReload)
				{
					FVector PointToShot = RootComponent->GetComponentLocation() + GetCharRotation().Vector()*100.f;
					if (FirstWeapon->FirstFire(UGameplayStatics::GetPlayerController(GetWorld(), 0), PointToShot, GetCharRotation()))
					{
						FireBNE(FirstWeapon, true, true);
						StopReloading();
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("FirstWeapon: OUT OF AMMO!"));
						FireBNE(FirstWeapon, true, false);
					}
					CanPrimeFire = false;
					GetWorldTimerManager().SetTimer(PrimeFireTimer, this, &AMC_Char::PrimeFireWayAround, FirstWeapon->GetFirstFireRate(), false);
				}
			}
			else
			{
				if (SecondWeapon->GetShotGunStyle() || !IsReload)
				{
					FVector PointToShot = RootComponent->GetComponentLocation() + GetCharRotation().Vector()*100.f;
					if (SecondWeapon->FirstFire(UGameplayStatics::GetPlayerController(GetWorld(), 0), PointToShot, GetCharRotation()))
					{
						FireBNE(SecondWeapon, true, true);
						StopReloading();
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("SecondWeapon: OUT OF AMMO!"));
						FireBNE(SecondWeapon, true, false);
					}
					CanPrimeFire = false;
					GetWorldTimerManager().SetTimer(PrimeFireTimer, this, &AMC_Char::PrimeFireWayAround, SecondWeapon->GetFirstFireRate(), false);
				}
			}
		}
	}
}

void AMC_Char::PrimeFireWayAround()
{
	CanPrimeFire = true;
	if (FirstWeapon->GetIsFA())
	{
		bool IsKeyDown = false;
		TArray<FInputActionKeyMapping> KeysArray = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeysForAction("PrimeFire");
		for (int i = 0; i < KeysArray.Num(); i++)
		{
			FKey Key = KeysArray[i].Key;
			if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(Key))
			{
				IsKeyDown = true;
			}
		}

		if (IsKeyDown)
		{
			PrimeFire();
		}
	}
}


void AMC_Char::AlternativeFire()
{
	if (UKismetMathLibrary::SelectObject(FirstWeapon, SecondWeapon, IsFirstWeapon)->IsValidLowLevel())
	{
		if(CanAlternativeFire)
		{
			if (IsFirstWeapon)
			{
				if (FirstWeapon->GetShotGunStyle() || !IsReload)
				{
					FVector PointToShot = RootComponent->GetComponentLocation() + GetCharRotation().Vector()*100.f;
					if (FirstWeapon->SecondFire(UGameplayStatics::GetPlayerController(GetWorld(), 0), PointToShot, GetCharRotation()))
					{
						FireBNE(FirstWeapon, false, true);
						StopReloading();
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("FirstWeapon: OUT OF AMMO!"));
						FireBNE(FirstWeapon, false, false);
					}

					CanAlternativeFire = false;
					GetWorldTimerManager().SetTimer(AlternativeFireTimer, this, &AMC_Char::AlternativeFireWayAround, FirstWeapon->GetSecondFireRate(), false);
				}
			}
			else 
			{
				if (SecondWeapon->GetShotGunStyle() || !IsReload)
				{
					FVector PointToShot = RootComponent->GetComponentLocation() + GetCharRotation().Vector()*100.f;
					if (SecondWeapon->SecondFire(UGameplayStatics::GetPlayerController(GetWorld(), 0), PointToShot, GetCharRotation()))
					{
						FireBNE(SecondWeapon, false, true);
						StopReloading();
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("SecondWeapon: OUT OF AMMO!"));
						FireBNE(SecondWeapon, false, false);
					}

					CanAlternativeFire = false;
					GetWorldTimerManager().SetTimer(AlternativeFireTimer, this, &AMC_Char::AlternativeFireWayAround, SecondWeapon->GetSecondFireRate(), false);
				}
			}
		}
	}
}

void AMC_Char::AlternativeFireWayAround()
{
	CanAlternativeFire = true;

	if (FirstWeapon->GetIsSA())
	{
		bool IsKeyDown = false;
		TArray<FInputActionKeyMapping> KeysArray = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerInput->GetKeysForAction("AlternativeFire");
		for (int i = 0; i < KeysArray.Num(); i++)
		{
			FKey Key = KeysArray[i].Key;
			if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(Key))
			{
				IsKeyDown = true;
			}
		}
		if (IsKeyDown)
		{
			AlternativeFire();
		}
	}
}

	//----------------------------------
	// Desh staf

void AMC_Char::StartDesh(FVector DirectionToDeshRef)
{
	UWorld* World = GetWorld();
	if (World != NULL)
	{

		if (!World->GetTimerManager().IsTimerActive(DeshTimer))
		{
			LengthsArray.Empty();
			ArraySum = 0;
			for (int i = 0; i < NumberOfSmallDeshes; i++)
			{
				float li;
				li = StartDeshSpeed * NumberOfSmallDeshes / DeshTime;
				li += (SinHight * NumberOfSmallDeshes / DeshTime) * UKismetMathLibrary::Sin((ASinConst + (UKismetMathLibrary::Conv_IntToFloat(i) / UKismetMathLibrary::Conv_IntToFloat(NumberOfSmallDeshes)) * (180.f - ASinConst - BSinConst)) * 3.14159f / 180.f);

				li = li / 1000.f;


				ArraySum += li;

				LengthsArray.Add(li);
			}


			Coefficient = DeshLength / ArraySum;

			CountOfSmallDeshes = 0;
			DirectionToDesh = DirectionToDeshRef;
			World->GetTimerManager().SetTimer(DeshTimer, this, &AMC_Char::DeshCicle, DeshTime / NumberOfSmallDeshes, true, DeshTime / NumberOfSmallDeshes);

			TArray<AActor*> TestArray;

			UGameplayStatics::GetAllActorsOfClass(this, AEnemy_Char::StaticClass(), TestArray);

			for (int i = 0; i < TestArray.Num(); i++)
			{
				if (TestArray[i]->IsValidLowLevel())
				{
					AEnemy_Char* TestActor = Cast<AEnemy_Char>(TestArray[i]);
					if (TestActor)
						TestActor->StartEnemyDelay(DeshEnemyDelay);
				}
			}
		}
	}

}

void AMC_Char::DeshCicle()
{
	UWorld* World = GetWorld();
	if (World != NULL)
	{



		DirectionToDesh = DirectionToDesh / DirectionToDesh.Size();


		FVector Start = GetActorLocation();
		FVector End = Start + DirectionToDesh * 60.f;

		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, this);
		TraceParams.bTraceComplex = true;
		TraceParams.AddIgnoredActor(this);
		FHitResult HitOut;
		ECollisionChannel CollisionChannel = ECC_Pawn;

		if (CountOfSmallDeshes >= LengthsArray.Num())
		{
			StopDesh();
		}

		else
		{

			if (World->LineTraceSingleByChannel(HitOut, Start, End, CollisionChannel, TraceParams))
			{
				StopDesh();
			}
			else
			{
				SetActorLocation(GetActorLocation() + DirectionToDesh * LengthsArray[CountOfSmallDeshes] * Coefficient);
				CountOfSmallDeshes++;
			}
		}
	}
}

void AMC_Char::StopDesh()
{
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		World->GetTimerManager().ClearTimer(DeshTimer);

		if (UKismetMathLibrary::Conv_IntToFloat(CountOfSmallDeshes) / UKismetMathLibrary::Conv_IntToFloat(NumberOfSmallDeshes) < 0.5f)
		{
			TArray<AActor*> TestArray;

			UGameplayStatics::GetAllActorsOfClass(this, AEnemy_Char::StaticClass(), TestArray);

			for (int i = 0; i < TestArray.Num(); i++)
			{
				if (TestArray[i]->IsValidLowLevel())
				{
					AEnemy_Char* TestActor = Cast<AEnemy_Char>(TestArray[i]);
					if (TestActor)
						TestActor->StopEnemyDelay();
				}
			}
		}

	}
}