// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemies/Projectile.h"
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
	FTimerHandle ShootingTimerHandle;

protected:

	virtual void BeginPlay() override;

	void ChasingPlayer();

	void ShootProjectile();

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DroneMesh;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* DroneCapsule;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	float ShootingRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float TimeBetweenShots = 1.0f;



};
