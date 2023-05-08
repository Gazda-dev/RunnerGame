// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"



void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Coins = CreateWidget(this, CoinsClass);

	if (Coins)
	{
		Coins->AddToViewport();
	}
}
