// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/CharPawn.h"
#include "Objects/Weapons/MC_Weapon.h"
#include "Projectails/Projectail.h"
#include "Components/ArrowComponent.h"
#include "MC_Char.generated.h"

UCLASS()
class DEMO_001_API AMC_Char : public ACharPawn
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* CameraRotationArrow;




public:
	// Sets default values for this character's properties
	AMC_Char();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComp) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//Переменные для камеры
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraInterpLerpAlfa;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraInterpSpeed;

	//Переменная показывает вращать камеру в данный момент или нет
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	bool IsRotateCamera;

	//Данные переменные содержат объекты оружий и используются для реализации стрельбы
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	UMC_Weapon* FirstWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	UMC_Weapon* SecondWeapon;

	UFUNCTION(BlueprintPure, Category = Character)
	FRotator GetCharRotation();

	//Переменные показывающие может ли сейчас производиться огонь
	bool CanPrimeFire;
	bool CanAlternativeFire;

	UFUNCTION(BlueprintPure, Category = Character)
	bool GetIsFirstWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void ChangeWeapon();

	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	void ChangeWeapon_BNE();
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void StartChangeWeapon();

	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	void StartChangeWeapon_BNE();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void StopChangeWeapon();

	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	void StopChangeWeapon_BNE();
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void StartReload();

	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	void StartReload_BNE();
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void ReloadWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void StopReloading();

	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	void StopReloading_BNE();
		
	UFUNCTION(BlueprintPure, Category = Weapon)
	bool GetIsReload();

	UFUNCTION(BlueprintPure, Category = Character)
	FVector GetCharLookPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharMesh)
	bool IsRotateCharMesh;

	UFUNCTION(BlueprintPure, Category = Weapon)
	bool DoesHasWeapon(TSubclassOf<UMC_Weapon> WeaponToCheck) {

		if (FirstWeapon->IsValidLowLevel())
			if (FirstWeapon->GetClass() == WeaponToCheck)
				return true;

		if (SecondWeapon->IsValidLowLevel())
			if (SecondWeapon->GetClass() == WeaponToCheck)
				return true;

		return false;
	}

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = Walk)
	void WalkFunction(FVector Direction, float Value);

	void InterpWalk(float DeltaTimeWalkInterp);

	FVector DirectionVector;

	float DirectionValue;

	float ForwardMoveValue;

	float RightMoveValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InterpSpeed)
	float InterpWalkSpeedVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InterpSpeed)
	float InterpWalkSpeedValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InterpSpeed)
	float PercentOfValue;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Desh)
	void Desh_Event_Implementation(FVector DeshDirection);

	//Данные функции отвечают за ведение огня

	UFUNCTION(BlueprintCallable, Category = Fire)
	void PrimeFire();
	UFUNCTION(BlueprintCallable, Category = Fire)
	void AlternativeFire();
	
	UFUNCTION(BlueprintImplementableEvent, Category = Fire)
	void FireBNE(UMC_Weapon* Weapon, bool IsPrimeFire, bool FireOrMisfire);

	//Данная функция запускает объект первой способности
	void UseDesh();

	UFUNCTION(BlueprintCallable, Category = Spining)
	void UseSpining();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Desh)
	void Spining_Event_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	bool IsReload;

	UPROPERTY(BlueprintReadWrite, Category = HP)
	bool bCanMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Desh)
	float DeshEnemyDelay;

private:
	
	//Функция отвечает за интерполяцию камеры между курсором и ГГ
	void InterpCamera(float DeltaSeconds);
	
	//Данные таймеры необходимы для ведения постоянного огня
	FTimerHandle PrimeFireTimer;
	FTimerHandle AlternativeFireTimer;

	//Функции для обходного пути реализации стрельбы
	void PrimeFireWayAround();
	void AlternativeFireWayAround();

	//Показывает ротацию поворота прицела/меша/персонажа
	FRotator CharRotation;

	//Показывает какое оружие сейчас активно
	bool IsFirstWeapon;

	//Показывает мышку персонажа
	FVector CharLookPoint;
	
	FTimerHandle ReloadTimer;

	FTimerHandle ChangeWeaponTimer;

	// Spining staf -------------------

	void SpiningCicle();

	UFUNCTION(BlueprintCallable, Category = Spining)
	void StopSpining();

	int NumOfSpining;
	
	//-------------------------------
	// Desh staf

protected:

	UFUNCTION(BlueprintCallable, Category = AISkills)
		void StartDesh(FVector DirectionToDeshRef);

	void DeshCicle();

	void StopDesh();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Desh)
		float Coefficient;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Desh)
		TArray<float> LengthsArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spining)
	float SpiningRadius = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spining)
	float SpiningTime = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spining)
		bool ShowSpiningSphere = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spining)
	int SpiningStatus = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Desh)
	float DeshLength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Desh)
	float DeshTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Desh)
	float ASinConst;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Desh)
	float BSinConst;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Desh)
	float SinHight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Desh)
	float StartDeshSpeed;

	bool IsCanSpining() { return !GetWorldTimerManager().IsTimerActive(ReloadSpiningTimer); }
	bool IsCanDesh() { return !GetWorldTimerManager().IsTimerActive(ReloadDeshTimer); }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Desh)
	float DeshReloadTime = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spining)
	float SpiningReloadTime = 0.5;

private:

	FTimerHandle ReloadSpiningTimer;
	FTimerHandle ReloadDeshTimer;

	int NumberOfSmallDeshes;
	int CountOfSmallDeshes;
	FTimerHandle DeshTimer;

	float ArraySum;

	FVector DirectionToDesh;

	FTimerHandle SpiningTimer;

};
