// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/DroneCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ADroneCharacter::ADroneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DroneCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Drone Capsule"));
	RootComponent = DroneCapsule;

	DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drone Mesh"));
	DroneMesh->SetupAttachment(GetRootComponent());
}


void ADroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = FMath::RandRange(0.f, 360.f);
	SetActorRotation(NewRotation);
}

void ADroneCharacter::ChasingPlayer()
{
	if (bShouldChasePlayer)
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (APawn* PlayerPawn = PlayerController->GetPawn())
			{
				FVector PlayerDirection = PlayerPawn->GetActorLocation();
				FVector DroneLocation = GetActorLocation();
				FVector DirectionToPlayer = PlayerDirection - DroneLocation;
				float DistanceToPlayer = DirectionToPlayer.Size();

				if (DistanceToPlayer > 500.f)
				{
					DirectionToPlayer.Normalize();
					float Speed = 150.f;
					FVector NewLocation = DroneLocation + DirectionToPlayer * Speed * GetWorld()->GetDeltaSeconds();

					float HoverAmplitude = 5.f;
					float HoverFrequency = 1.0f;
					NewLocation.Z += HoverAmplitude * FMath::Sin(HoverFrequency * GetWorld()->GetTimeSeconds());

					FRotator DesiredRotation = DirectionToPlayer.Rotation();
					FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), DesiredRotation, GetWorld()->GetDeltaSeconds(), 2.0f);
					float RotationAmplitude = 5.f;
					float RotationFrequency = 0.5f;
					SmoothRotation.Yaw += RotationAmplitude * FMath::Sin(RotationFrequency * GetWorld()->GetTimeSeconds());

					SetActorLocationAndRotation(NewLocation, SmoothRotation);
				}
			}
		}
	}

}


void ADroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChasingPlayer();
}


void ADroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

