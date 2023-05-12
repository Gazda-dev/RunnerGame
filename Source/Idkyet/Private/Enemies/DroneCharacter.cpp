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
	
}

void ADroneCharacter::ChasingPlayer()
{


}


void ADroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldChasePlayer)
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (APawn* PlayerPawn = PlayerController->GetPawn())
			{
				FVector PlayerDirection = PlayerPawn->GetActorLocation() - GetActorLocation();
				PlayerDirection.Normalize();

				FVector NewLocation = GetActorLocation() + PlayerDirection * DroneMovementSpeed * DeltaTime;
				SetActorLocation(NewLocation);
			}
		}
	}
}


void ADroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

