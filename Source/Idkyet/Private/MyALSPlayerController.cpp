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

	FString levelName = UGameplayStatics::GetCurrentLevelName(this);
	if (levelName == "Menu2")
	{
		MenuMap();
	}
	else if (levelName == "Main")
	{
		OnLevel1Loaded();
	}
	//else if (levelName == "TutorialMap")
	//{
	//	TutorialLevel();
	//}
	//else
	//{
		UE_LOG(LogTemp, Warning, TEXT("heyyyyyy"));
	//}

}


void AMyALSPlayerController::MenuMap()
{
	if (MenuScreenClass)
	{
		Menu = CreateWidget<UUserWidget>(GetWorld(), MenuScreenClass);

		if (Menu)
		{
			Menu->AddToViewport();
			DisableAllInputs();
		}
	}
	bIsGameStarted = false;
	if (SettingsMenu)
	{
		SettingsMenu->RemoveFromParent();
	}
}

void AMyALSPlayerController::OpenChooseLevelName()
{
	ChooseLevelMenu = CreateWidget<UUserWidget>(GetWorld(), ChooseLevelClass);

	if (Menu)
	{
		Menu->RemoveFromParent();
	}
	if (ChooseLevelMenu)
	{
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
	DisableAllInputs();
}

void AMyALSPlayerController::TutorialLevel()
{
	UE_LOG(LogTemp, Display, TEXT("Tutorial opened"));
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
	UE_LOG(LogTemp, Display, TEXT("Level1 opened"));
	FString LevelName = "Main";
	UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
	//FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyALSPlayerController::OnLevel1Loaded, 1.0f, false);
	//
	//FLatentActionInfo LatentInfo;
	//LatentInfo.CallbackTarget = this;
	//LatentInfo.ExecutionFunction = FName("OnLevel1Loaded");
	//LatentInfo.UUID = 1;
	//LatentInfo.Linkage = 0;

	//UGameplayStatics::LoadStreamLevel(this, FName(*LevelName), true, false, LatentInfo);
	OnLevel1Loaded();
}


void AMyALSPlayerController::OnLevel1Loaded()
{
	if (Menu)
	{
		Menu->RemoveFromParent();
	}

	if (ChooseLevelMenu)
	{
		ChooseLevelMenu->RemoveFromParent();
	}

	EnableAllInputs();

	ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
	if (ScoreWidget)
	{
		UE_LOG(LogTemp, Display, TEXT("Score added"));
		ScoreWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Score not added"));
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

