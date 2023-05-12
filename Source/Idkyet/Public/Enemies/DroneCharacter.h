// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DroneCharacter.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class IDKYET_API ADroneCharacter : public APawn
{
	GENERATED_BODY()

public:

	ADroneCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool bShouldChasePlayer = false;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Drone movement #cpp")
	float DroneMovementSpeed = 10.f;

	void ChasingPlayer();

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DroneMesh;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* DroneCapsule;



};
