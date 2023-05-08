// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class IDKYET_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AMainCharacter();
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddCoins(int32 Value);



	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsValueChanged, int32, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "Coins_cpp")
	FOnCoinsValueChanged OnCoinsValueChanged;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_cpp")
	UInputMappingContext* CharacterMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_cpp")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_cpp")
	UInputAction* JumpAction;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets_cpp")
	//TSubclassOf<UUserWidget> ScoreWidgetClass;

	//UPROPERTY()
	//class UScoreWidget* ScoreWidget;

	void MoveRight(const FInputActionValue& Value);

	float TotalDistanceMoved = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score_cpp")
	int32 TotalValue = 0;

	UFUNCTION(BlueprintPure, Category = "Score_cpp")
	int32 GetTotalValue() const
	{
		return TotalValue;
	}

	FVector Start;
	FVector Current;
private:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;


};
