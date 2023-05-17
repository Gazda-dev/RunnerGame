// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyALSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Obstacles/WallActor.h"
#include "Animation/AnimMontage.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MyALSPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Saving/SG_SaveGame.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

AMyALSCharacter::AMyALSCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
    Health = MaxHealth;

    BackgroundSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Background Sound"));
    BackgroundSoundComponent->SetupAttachment(GetRootComponent());
}

void AMyALSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bLevelIsActive)
    {
        CalculateTime();
        CalculateDistance();
    }
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


    FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
    UE_LOG(LogTemp, Warning, TEXT("Current level name: %s"), *LevelName);

    if (BackgroundSoundComponent && BackgroundSoundCue)
    {
        BackgroundSoundComponent->SetSound(BackgroundSoundCue);
        BackgroundSoundComponent->Play();

    }
}

void AMyALSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpingAction, ETriggerEvent::Triggered, this, &AMyALSCharacter::JumpingMontage);
        EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Triggered, this, &AMyALSCharacter::PauseGame);
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
        const int32 Selection = FMath::RandRange(0, 2);
        FName SectionName = FName();
        switch (Selection)
        {
        case 0:
            SectionName = FName("Jump1");
            break;

        case 1:
            SectionName = FName("Jump2");
            break;

        case 2:
            SectionName = FName("Jump3");
            break;

        default:
            break;
        }
        AnimInstance->Montage_JumpToSection(SectionName, JumpsMontage);

        if (HitCameraShakeClass)
        {
            GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
        }


    }
}

void AMyALSCharacter::OnJumpMontageEnd()
{
    UE_LOG(LogTemp, Display, TEXT("EndNotify - Collisions enabled"));
    FVector DefaultLocation = GetCapsuleComponent()->GetRelativeLocation();
    //DefaultLocation.Z -= 70.f;
    GetCapsuleComponent()->SetRelativeLocation(DefaultLocation);
}

void AMyALSCharacter::OnJumpMontageStart()
{
    UE_LOG(LogTemp, Display, TEXT("Start notify - Collisions disabled"));
    FVector NewLocation = GetCapsuleComponent()->GetRelativeLocation();
    NewLocation.Z += 150.f;
    GetCapsuleComponent()->SetRelativeLocation(NewLocation);

}

float AMyALSCharacter::GetHealthPercent() const
{
    return Health / MaxHealth;
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

void AMyALSCharacter::PauseGame()
{
    if (AMyALSPlayerController* MyController = Cast<AMyALSPlayerController>(GetController()))
    {
        MyController->PauseGame();
    }
    
}

void AMyALSCharacter::StartLevel()
{
    LevelStartTime = GetWorld()->GetTimeSeconds();
    bLevelIsActive = true;
}

void AMyALSCharacter::EndLevel()
{
    CalculateTime();
    SavingGame();
    bLevelIsActive = false;
}

void AMyALSCharacter::CalculateTime()
{
    LevelEndTime = GetWorld()->GetTimeSeconds();
    LevelTime = LevelEndTime - LevelStartTime;
}

void AMyALSCharacter::SaveBestTime()
{
    if (LevelTime < BestTime || BestTime == 0)
    {
        BestTime = LevelTime;
        UE_LOG(LogTemp, Warning, TEXT("New BestTime: %f"), BestTime);
        USG_SaveGame* SaveGame = Cast<USG_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("ScoreSaveGame"), 0));
        if (SaveGame)
        {
            SaveGame->BestTime = BestTime;
            UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("ScoreSaveGame"), 0);
            UE_LOG(LogTemp, Warning, TEXT("BestTime saved: %f"), SaveGame->BestTime);
        }
    }
}

void AMyALSCharacter::SavingGame()
{
    USG_SaveGame* SaveGame = Cast<USG_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("ScoreSaveGame"), 0));
    UE_LOG(LogTemp, Warning, TEXT("Loaded Game"));
    if (!SaveGame)
    {
        SaveGame = Cast<USG_SaveGame>(UGameplayStatics::CreateSaveGameObject(USG_SaveGame::StaticClass()));
    }
    LevelEndTime = GetWorld()->GetTimeSeconds();
    LevelTime = LevelEndTime - LevelStartTime;
    if (LevelTime < SaveGame->BestTime || SaveGame->BestTime == 0)
    {
        SaveGame->BestTime = LevelTime;
        UE_LOG(LogTemp, Display, TEXT("Nwe Best Time: %f"), SaveGame->BestTime);
    }

    int32 CurrentCoins = GetTotalValue();
    if (CurrentCoins > SaveGame->BestCoins)
    {
        SaveGame->BestCoins = CurrentCoins;
    }

    UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("ScoreSaveGame"), 0);
    UE_LOG(LogTemp, Warning, TEXT("Saved Game"));
}

void AMyALSCharacter::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* DamageInstigator, AActor* DamageCauser)
{
    if (Damage <= 0.f) return;

    Health -= Damage;
    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

    if (Health <= 0.f)
    {
        if (AMyALSPlayerController* MyController = Cast<AMyALSPlayerController>(GetController()))
        {
            RagdollStart();
            MyController->DeadHandle();
        }
       
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

