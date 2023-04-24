// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "HUD/ScoreManager.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CharacterMapping, 0);
		}
	}

	/*if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
		ScoreWidget->AddToViewport();
	}*/
}

void AMainCharacter::MoveRight(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();
	if (Controller && (DirectionValue != 0.f))
	{
		FVector Right = GetActorRightVector();
		AddMovementInput(Right, DirectionValue);
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::MoveRight);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}

}

void AMainCharacter::AddCoins(int32 Value)
{
	if (UScoreManager* ScoreManager = Cast<UScoreManager>(StaticFindObject(UScoreManager::StaticClass(), nullptr, TEXT("/Game/RunnerGame/MyGameInstance.MyGameInstance:ScoreManager"))))
	{
		ScoreManager->AddScore(Value);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find ScoreManager"));
	}
}

