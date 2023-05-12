// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_GameModeBase.generated.h"


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

	UFUNCTION(BlueprintCallable)
	void OpenSettingsMenu();

	UFUNCTION(BlueprintCallable)
	void CloseSettingsMenu();

	UFUNCTION(BlueprintCallable)
	void ApplySettings();

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MenuScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> SettingsScreenClass;

	UPROPERTY()
	UUserWidget* Menu;

	UPROPERTY()
	UUserWidget* SettingsMenu;

	void DisableAllInputs();
	void EnableAllInputs();

	bool bIsSettingsMenuOpen = false;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode #cpp")
	TSubclassOf<class ADroneCharacter> DroneCharacterClass;

	UPROPERTY()
	ADroneCharacter* DroneCharacter;

};
