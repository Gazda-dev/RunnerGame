// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/ALSCharacter.h"
#include "MyALSCharacter.generated.h"

/**
 * 
 */
class UAnimMontage;

UCLASS()
class IDKYET_API AMyALSCharacter : public AALSCharacter
{
	GENERATED_BODY()

public:

	AMyALSCharacter(const FObjectInitializer& ObjectInitializer);

	void AddCoins(int32 Value);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsValueChanged, int32, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "Coins_cpp")
	FOnCoinsValueChanged OnCoinsValueChanged;

	UFUNCTION(BlueprintPure, Category = "Score_cpp")
	int32 GetTotalValue() const
	{
		return TotalValue;
	}

	UFUNCTION(BlueprintPure, Category = "Score_cpp")
	int32 GetTotalDistancemoved() const
	{
		return TotalDistanceMoved;
	}


	UFUNCTION(BlueprintPure, Category = "Score_cpp")
	float GetLevelTime() const
	{
		return LevelTime;
	}

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool bCameraShake = false;
	bool bIsInLevel = false;

	UPROPERTY(BlueprintReadWrite)
	FVector StartPosition;

	UFUNCTION()
	void OnJumpMontageEnd();

	UFUNCTION()
	void OnJumpMontageStart();

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void SavingGame();

	void StartLevel();
	void EndLevel();
	
	UPROPERTY(EditAnywhere, Category = "Health #cpp")
	float Health = 2.f;
protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Audio #cpp")
	UAudioComponent* BackgroundSoundComponent;

	UPROPERTY(EditAnywhere, Category = "Audio #cpp")
	class USoundCue* BackgroundSoundCue;

	int32 TotalDistanceMoved = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score_cpp")
	int32 TotalValue = 0;

	FVector Start;
	FVector Current;

	void CalculateDistance();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input #cpp")
	class UInputAction* JumpingAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input #cpp")
		class UInputAction* MenuAction;

	void JumpingMontage();
	void ShowMenu();
	void HideMenu();
	void PauseGame();


	/*
	* Time
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time #cpp")
	float LevelStartTime = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time #cpp")
	float LevelEndTime = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time #cpp")
	float BestTime = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time #cpp")
	float LevelTime = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time #cpp")
	bool bLevelIsActive = false;

	void CalculateTime();
	void SaveBestTime();

	/*
	* Time End
	*/

private:

	float CheckpointDistance = 0.f;
	float CheckpointXPosition = 0.f;
	bool bIsMovingForward = true;
	float MinCheckpointDistance = 50.f;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 5.f;


	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* DamageInstigator, AActor* DamageCauser);

	bool bIsTouchingWall();

	UPROPERTY(EditDefaultsOnly, Category = "Montages #cpp")
	UAnimMontage* JumpsMontage;

	UPROPERTY(EditAnywhere, Category = "#cpp")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	UPROPERTY(EditAnywhere, Category = "#cpp")
	TSubclassOf<class UCameraShakeBase> DefaultCameraShakeClass;
};
