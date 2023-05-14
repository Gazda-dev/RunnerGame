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

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	int32 TotalDistanceMoved = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score_cpp")
	int32 TotalValue = 0;

	FVector Start;
	FVector Current;

	void CalculateDistance();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input #cpp")
	class UInputAction* JumpingAction;

	void Jumping();

private:

	float CheckpointDistance = 0.f;
	float CheckpointXPosition = 0.f;
	bool bIsMovingForward = true;
	float MinCheckpointDistance = 50.f;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 5.f;
	float Health = 0.f;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* DamageInstigator, AActor* DamageCauser);

	bool bIsTouchingWall();

	UPROPERTY(EditDefaultsOnly, Category = "Montages #cpp")
	UAnimMontage* WallRunMontage;
};
