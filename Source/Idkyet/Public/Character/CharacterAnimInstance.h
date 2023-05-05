// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class IDKYET_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	virtual void NativeInitializeAnimation() override;


	UPROPERTY(BlueprintReadOnly)
	class AMainCharacter* MainCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement_anim_cpp)
	class UCharacterMovementComponent* MainCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement_anim_cpp)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement_anim_cpp)
	bool bIsFalling;
};
