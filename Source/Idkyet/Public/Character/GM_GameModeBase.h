// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_GameModeBase.generated.h"

class UUserWidget;

UCLASS()
class IDKYET_API AGM_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void ExitGame();

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MenuScreenWidget;

	UPROPERTY()
	UUserWidget* Menu;
};
