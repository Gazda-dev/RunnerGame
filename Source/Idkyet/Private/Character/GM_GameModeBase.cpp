// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GM_GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AGM_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Menu = CreateWidget(this, MenuScreenWidget);

	if (Menu)
	{
		Menu->AddToViewport();
	}
}

void AGM_GameModeBase::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Game started -> GameMode"));
}

void AGM_GameModeBase::ExitGame()
{
}
