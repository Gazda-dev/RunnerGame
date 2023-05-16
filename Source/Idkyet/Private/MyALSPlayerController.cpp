// Fill out your copyright notice in the Description page of Project Settings.


#include "MyALSPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Enemies/DroneCharacter.h"
#include "Character/MyALSCharacter.h"
#include "GameFramework/PlayerStart.h"

void AMyALSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MenuMap();
}


void AMyALSPlayerController::MenuMap()
{
	//FString LevelName = "MenuMap";
	//UGameplayStatics::OpenLevel(this, FName(*LevelName));

	if (MenuScreenClass)
	{
		Menu = CreateWidget<UUserWidget>(GetWorld(), MenuScreenClass);

		if (Menu)
		{
			Menu->AddToViewport();
			DisableAllInputs();
		}
	}
}

void AMyALSPlayerController::OpenChooseLevelName()
{
	ChooseLevelMenu = CreateWidget<UUserWidget>(GetWorld(), ChooseLevelClass);

	if (Menu && ChooseLevelMenu)
	{
		Menu->RemoveFromParent();
		ChooseLevelMenu->AddToViewport();
	}
	if (EndGameWidget)
	{
		EndGameWidget->RemoveFromParent();
	}
}

void AMyALSPlayerController::HideMenu()
{
	if (Menu)
	{
		Menu->RemoveFromParent();
	}
}

void AMyALSPlayerController::PauseGame()
{
	SetPause(true);
	
	PauseMenu = CreateWidget(this, PauseMenuClass);
	if (PauseMenu)
	{
		DisableAllInputs();
		PauseMenu->AddToViewport();
	}
}

void AMyALSPlayerController::ResumeGameFromPause()
{
	SetPause(false);
	if (PauseMenu)
	{
		PauseMenu->RemoveFromParent();
		EnableAllInputs();
	}
}

void AMyALSPlayerController::EndGameHandle()
{
	EndGameWidget = CreateWidget<UUserWidget>(GetWorld(), EndGameWidgetClass);
	if (EndGameWidget)
	{
		EndGameWidget->AddToViewport();
	}
}

void AMyALSPlayerController::TutorialLevel()
{
	if (Menu && ChooseLevelMenu)
	{
		Menu->RemoveFromParent();
		ChooseLevelMenu->RemoveFromParent();
	}

	FString TutorialLevel = "TutorialMap";
	UGameplayStatics::OpenLevel(this, FName(*TutorialLevel));

	EnableAllInputs();

	ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
	if (ScoreWidget)
	{
		ScoreWidget->AddToViewport();
	}

	if (AMyALSCharacter* MainCharacter = Cast<AMyALSCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		MainCharacter->bIsInLevel = true;
		MainCharacter->bCameraShake = true;
	}
}

void AMyALSPlayerController::Level1()
{
	if (Menu && ChooseLevelMenu)
	{
		Menu->RemoveFromParent();
		ChooseLevelMenu->RemoveFromParent();
	}

	EnableAllInputs();

	ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
	if (ScoreWidget)
	{
		ScoreWidget->AddToViewport();
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

	if (DroneCharacter)
	{
		DroneCharacter->bShouldChasePlayer = true;
		UE_LOG(LogTemp, Warning, TEXT("shouldchaseplayer = %d"), DroneCharacter->bShouldChasePlayer ? 1 : 0);
	}
	if (AMyALSCharacter* MainCharacter = Cast<AMyALSCharacter>(GetPawn()))
	{
		MainCharacter->bIsInLevel = true;
		MainCharacter->bCameraShake = true;
		MainCharacter->StartLevel();

		TArray<AActor*> FoundActors;
		AActor* PlayerStart = nullptr;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		if (FoundActors.Num() > 0)
		{
			PlayerStart = FoundActors[0];
			MainCharacter->StartPosition = PlayerStart->GetActorLocation();
		}
	}

}



//void AMyALSPlayerController::StartGame()
//{
//	EnableAllInputs();
//	if (Menu)
//	{
//		Menu->RemoveFromParent();
//	}
//
//	if (DroneCharacter)
//	{
//		DroneCharacter->bShouldChasePlayer = true;
//		UE_LOG(LogTemp, Warning, TEXT("shouldchaseplayer = %d"), DroneCharacter->bShouldChasePlayer ? 1 : 0);
//	}
//
//	ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
//	if (ScoreWidget)
//	{
//		ScoreWidget->AddToViewport();
//	}
//}

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
