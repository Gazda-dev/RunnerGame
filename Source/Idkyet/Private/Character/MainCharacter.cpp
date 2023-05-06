// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "HUD/ScoreManager.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"



AMainCharacter::AMainCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


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
}


void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMainCharacter::MoveRight(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();
	if (Controller && (DirectionValue != 0.f))
	{
		FVector PreviousLocation = GetActorLocation();

		FVector Right = GetActorForwardVector();
		AddMovementInput(Right, DirectionValue);

		FVector CurrentLocation = GetActorLocation();
		float DistanceMoved = (CurrentLocation - PreviousLocation).Size() * 100.f;
		TotalDistanceMoved += DistanceMoved;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Distance: %.2f m"), TotalDistanceMoved / 100.f));
		}
	}
}

void AMainCharacter::Run(float DeltaTime)
{
	FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward);

	float DistanceMoved = Forward.Size() * DeltaTime;
	TotalDistanceMoved += DistanceMoved;
	if (GEngine)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gengine is cool"));
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), TotalDistanceMoved));
	}

	//if (TotalDistanceMoved > 5.f)
	//{
	//	float NewSpeed = GetCharacterMovement()->MaxWalkSpeed + 100.f;
	//	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	//}
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

}

