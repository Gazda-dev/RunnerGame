// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ALSPlayerController.h"
#include "MyALSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class IDKYET_API AMyALSPlayerController : public AALSPlayerController
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

	UFUNCTION(BlueprintCallable)
		void MenuMap();

	UFUNCTION(BlueprintCallable)
		void TutorialLevel();

	UFUNCTION(BlueprintCallable)
		void Level1();

	UFUNCTION(BlueprintCallable)
		void OpenChooseLevelName();

	UFUNCTION(BlueprintCallable)
		void HideMenu();

private:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> MenuScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> SettingsScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> ChooseLevelClass;
	
	UPROPERTY()
		UUserWidget* ScoreWidget;

	UPROPERTY()
		UUserWidget* Menu;

	UPROPERTY()
		UUserWidget* SettingsMenu;

	UPROPERTY()
		UUserWidget* ChooseLevelMenu;

	void DisableAllInputs();
	void EnableAllInputs();

	bool bIsSettingsMenuOpen = false;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode #cpp")
		TSubclassOf<class ADroneCharacter> DroneCharacterClass;

	UPROPERTY()
		ADroneCharacter* DroneCharacter;

};
