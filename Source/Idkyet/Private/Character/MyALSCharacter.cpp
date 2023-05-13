// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyALSCharacter.h"

AMyALSCharacter::AMyALSCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}


void AMyALSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyALSCharacter::BeginPlay()
{
	Super::BeginPlay();

    Start = GetActorLocation();
}

void AMyALSCharacter::CalculateDistance()
{
    Current = GetActorLocation();
    float DistanceMoved = FMath::Abs(Start.X - Current.X);

    if (GetVelocity().X > 0.f)
    {
        if (bIsMovingForward)
        {
            // Check if the player has moved far enough from the last checkpoint to set a new one
            if (Current.X >= CheckpointXPosition + MinCheckpointDistance)
            {
                TotalDistanceMoved = CheckpointDistance + DistanceMoved;
                CheckpointDistance = TotalDistanceMoved;
                CheckpointXPosition = Current.X;
            }
            else
            {
                TotalDistanceMoved = CheckpointDistance;
            }
        }
        else
        {
            CheckpointDistance = TotalDistanceMoved + DistanceMoved;
            CheckpointXPosition = Start.X;
            TotalDistanceMoved = CheckpointDistance;
            bIsMovingForward = true;
        }
    }
    else if (GetVelocity().X < 0.f)
    {
        if (!bIsMovingForward)
        {
            if (Current.X <= CheckpointXPosition - MinCheckpointDistance)
            {
                TotalDistanceMoved = CheckpointDistance;
                CheckpointXPosition = Current.X;
            }
        }
        else
        {
            CheckpointDistance = TotalDistanceMoved - DistanceMoved;
            CheckpointXPosition = Current.X;
            TotalDistanceMoved = CheckpointDistance;
            bIsMovingForward = false;
        }
    }
    Start = Current;
}


void AMyALSCharacter::AddCoins(int32 Value)
{
    TotalValue += Value;
    OnCoinsValueChanged.Broadcast(TotalValue);
}

float AMyALSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return 0.0f;
}
