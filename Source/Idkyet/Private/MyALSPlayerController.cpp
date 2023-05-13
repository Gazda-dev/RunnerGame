// Fill out your copyright notice in the Description page of Project Settings.


#include "MyALSPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Enemies/DroneCharacter.h"

void AMyALSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MenuScreenClass)
	{
		Menu = CreateWidget<UUserWidget>(GetWorld(), MenuScreenClass);

		if (Menu)
		{
			Menu->AddToViewport();
			DisableAllInputs();
		}
	}

	if (DroneCharacterClass)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DroneCharacterClass, FoundActors);
		if (FoundActors.Num() > 0)
		{
			DroneCharacter = Cast<ADroneCharacter>(FoundActors[0]);
		}
	}
}

void AMyALSPlayerController::StartGame()
{
	EnableAllInputs();
	if (Menu)
	{
		Menu->RemoveFromParent();
	}

	if (DroneCharacter)
	{
		DroneCharacter->bShouldChasePlayer = true;
		UE_LOG(LogTemp, Warning, TEXT("shouldchaseplayer = %d"), DroneCharacter->bShouldChasePlayer ? 1 : 0);
	}
}

void AMyALSPlayerController::ExitGame()
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0))
		{
			UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
		}
	}
}

void AMyALSPlayerController::OpenSettingsMenu()
{
	if (SettingsScreenClass && !bIsSettingsMenuOpen)
	{
		SettingsMenu = CreateWidget<UUserWidget>(GetWorld(), SettingsScreenClass);
		if (SettingsMenu)
		{
			if (Menu)
			{
				Menu->RemoveFromParent();
				SettingsMenu->AddToViewport();
				bIsSettingsMenuOpen = true;
				DisableAllInputs();
			}
		}
	}
}

void AMyALSPlayerController::CloseSettingsMenu()
{
	if (SettingsMenu && bIsSettingsMenuOpen)
	{
		SettingsMenu->RemoveFromParent();
		bIsSettingsMenuOpen = false;
	}
}

void AMyALSPlayerController::ApplySettings()
{
}

void AMyALSPlayerController::DisableAllInputs()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
	}
}

void AMyALSPlayerController::EnableAllInputs()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;
	}
}
