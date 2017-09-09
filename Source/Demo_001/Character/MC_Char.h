// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/CharPawn.h"
#include "Objects/Weapons/MC_Weapon.h"
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
	

	//Данная переменная содержит объект способности героя в виде рывка
	class UObject_Skills* Desh;

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

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
	void ChangeWeapon_BNE();
	void ChangeWeapon_BNE_Implementation();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void StartChangeWeapon();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
	void StartChangeWeapon_BNE();
	void StartChangeWeapon_BNE_Implementation();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void StopChangeWeapon();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
	void StopChangeWeapon_BNE();
	void StopChangeWeapon_BNE_Implementation();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void StartReload();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
	void StartReload_BNE();
	virtual void StartReload_BNE_Implementation();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void ReloadWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		void StopReloading();

	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
	void StopReloading_BNE();
	virtual void StopReloading_BNE_Implementation();
	
	UFUNCTION(BlueprintPure, Category = Weapon)
	bool GetIsReload();

	UFUNCTION(BlueprintPure, Category = Character)
	FVector GetCharLookPoint();

	UFUNCTION(BlueprintCallable, Category = TestCategory)
	float TestFunction(float TestRef);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharMesh)
	bool IsRotateCharMesh;

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
	
	UFUNCTION(BlueprintNativeEvent, Category = Fire)
	void FireBNE(UMC_Weapon* Weapon, bool IsPrimeFire, bool FireOrMisfire);
	virtual void FireBNE_Implementation(UMC_Weapon* Weapon, bool IsPrimeFire, bool FireOrMisfire);

	//Данная функция запускает объект первой способности
	void UseDesh();

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


private:

	int NumberOfSmallDeshes;
	int CountOfSmallDeshes;
	FTimerHandle DeshTimer;

	float ArraySum;


	FVector DirectionToDesh;

};
