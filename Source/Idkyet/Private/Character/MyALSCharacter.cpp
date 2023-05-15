// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyALSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Obstacles/WallActor.h"
#include "Animation/AnimMontage.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MyALSPlayerController.h"
#include "Components/CapsuleComponent.h"

AMyALSCharacter::AMyALSCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
    Health = MaxHealth;
}

void AMyALSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyALSCharacter::BeginPlay()
{
	Super::BeginPlay();

    Start = GetActorLocation();
    OnTakeAnyDamage.AddDynamic(this, &AMyALSCharacter::DamageTaken);

    if (DefaultCameraShakeClass && bCameraShake)
    {
        GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DefaultCameraShakeClass);
    }
}

void AMyALSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpingAction, ETriggerEvent::Triggered, this, &AMyALSCharacter::JumpingMontage);
        EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Triggered, this, &AMyALSCharacter::ShowMenu);
    }
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

void AMyALSCharacter::JumpingMontage()
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance && JumpsMontage)
    {
        AnimInstance->Montage_Play(JumpsMontage);
        const int32 Selection = FMath::RandRange(0, 3);
        FName SectionName = FName();
        switch (Selection)
        {
        case 0:
            SectionName = FName("Jump1");
            break;

        case 2:
            SectionName = FName("Jump2");
            break;

        case 3:
            SectionName = FName("Jump3");
            break;

        default:
            break;
        }

        if (HitCameraShakeClass)
        {
            GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
        }


    }
}

void AMyALSCharacter::OnJumpMontageEnd()
{
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AMyALSCharacter::OnJumpMontageStart()
{
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMyALSCharacter::ShowMenu()
{
    if (AMyALSPlayerController* PlayerController = Cast<AMyALSPlayerController>(GetController()))
    {

         PlayerController->MenuMap();
 
    }

}

void AMyALSCharacter::HideMenu()
{
    if (AMyALSPlayerController* PlayerController = Cast<AMyALSPlayerController>(GetController()))
    {

        PlayerController->HideMenu();

    }
}

void AMyALSCharacter::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* DamageInstigator, AActor* DamageCauser)
{
    if (Damage <= 0.f) return;

    Health -= Damage;
    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

    if (Health <= 0.f)
    {
        UGameplayStatics::OpenLevel(this, FName("Main"));
    }
}

bool AMyALSCharacter::bIsTouchingWall()
{
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors, AWallActor::StaticClass());

    //if overlapping with any wall return true
    return OverlappingActors.Num() > 0;
}


void AMyALSCharacter::AddCoins(int32 Value)
{
    TotalValue += Value;
    OnCoinsValueChanged.Broadcast(TotalValue);
}

