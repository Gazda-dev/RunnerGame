// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/DroneCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ADroneCharacter::ADroneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drone Mesh"));
	RootComponent = DroneMesh;


	DroneCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Drone Capsule"));
	DroneCapsule->SetupAttachment(GetRootComponent());

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(DroneMesh);
}


void ADroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = FMath::RandRange(0.f, 360.f);
	SetActorRotation(NewRotation);
}

void ADroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChasingPlayer();
}

void ADroneCharacter::ChasingPlayer()
{
	if (bShouldChasePlayer)
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (APawn* PlayerPawn = PlayerController->GetPawn())
			{
				DroneMesh->SetSimulatePhysics(true);
				FVector PlayerDirection = PlayerPawn->GetActorLocation();
				FVector DroneLocation = GetActorLocation();
				FVector DirectionToPlayer = PlayerDirection - DroneLocation;
				float DistanceToPlayer = DirectionToPlayer.Size();

				if (DistanceToPlayer <= ShootingRange)
				{
					//if the shooter timer isnt active, start it
					if (!GetWorld()->GetTimerManager().IsTimerActive(ShootingTimerHandle))
					{
						GetWorld()->GetTimerManager().SetTimer
						(
							ShootingTimerHandle,
							this,
							&ADroneCharacter::ShootProjectile,
							TimeBetweenShots,
							true
						);
					}
				}
				else
				{
					//if the shooting timer is active, clear it
					if (GetWorld()->GetTimerManager().IsTimerActive(ShootingTimerHandle))
					{
						GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
					}
				}

					DirectionToPlayer.Normalize();
					float Speed = 100.f;
					FVector Force = DirectionToPlayer * Speed;

					float TargetAltitude = 2500.f;
					float AltitudeError = TargetAltitude - DroneLocation.Z;
					float KP = 10.0f;
					float KI = 0.1f;
					float KD = 0.1f;
					static float Integral = 0.0f;
					static float PreviousError = 0.0f;
					Force.Z += KP * AltitudeError + KI * Integral + KD * (AltitudeError - PreviousError);
					PreviousError = AltitudeError;
					Integral += AltitudeError * GetWorld()->GetDeltaSeconds();

					float DampingFactor = 0.3f;
					FVector Velocity = DroneMesh->GetPhysicsLinearVelocity();
					FVector DampingForce = -Velocity * DampingFactor;
					Force += DampingForce;

					DroneMesh->AddForce(Force, NAME_None, true);

					FRotator DesiredRotation = DirectionToPlayer.Rotation();
					FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), DesiredRotation, GetWorld()->GetDeltaSeconds(), 2.0f);
					float RotationAmplitude = 0.5f;
					float RotationFrequency = 0.5f;
					SmoothRotation.Yaw += RotationAmplitude * FMath::Sin(RotationFrequency * GetWorld()->GetTimeSeconds());
					SetActorRotation(SmoothRotation);
				
			}
		}
	}

}

void ADroneCharacter::ShootProjectile()
{
	if (ProjectileClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const float ProjectileSpawnOffset = 100.0f;
		FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * ProjectileSpawnOffset);

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileClass,
				SpawnLocation,
				GetActorRotation(),
				SpawnParams
			);

		if (Projectile != nullptr)
		{
			Projectile->SetOwner(this);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ShootedProjectile"));
}



void ADroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

