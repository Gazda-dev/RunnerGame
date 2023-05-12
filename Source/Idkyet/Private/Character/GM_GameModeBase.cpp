// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GM_GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Enemies/DroneCharacter.h"

void AGM_GameModeBase::BeginPlay()
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

void AGM_GameModeBase::StartGame()
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

void AGM_GameModeBase::ExitGame()
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0))
		{
			UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
		}
	}
}

void AGM_GameModeBase::OpenSettingsMenu()
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

void AGM_GameModeBase::CloseSettingsMenu()
{
	if (SettingsMenu && bIsSettingsMenuOpen)
	{
		SettingsMenu->RemoveFromParent();
		bIsSettingsMenuOpen = false;
	}
}

void AGM_GameModeBase::ApplySettings()
{
}

void AGM_GameModeBase::DisableAllInputs()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
	}
}

void AGM_GameModeBase::EnableAllInputs()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;
	}
}
