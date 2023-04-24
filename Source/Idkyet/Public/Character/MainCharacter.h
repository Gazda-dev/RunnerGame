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

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_cpp")
	UInputMappingContext* CharacterMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input_cpp")
	UInputAction* MoveAction;

	void Move(const FInputActionValue& Value);

private:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;


};
