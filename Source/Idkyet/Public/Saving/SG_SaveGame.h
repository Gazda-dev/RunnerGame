// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SG_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class IDKYET_API USG_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, Category = "Score #cpp")
	int32 BestDistance = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Score #cpp")
	int32 BestCoins = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Score #cpp")
	float BestTime = 0.f;

	UFUNCTION(BlueprintPure, Category = "Score_cpp")
		int32 GetBestDistance() const
	{
		return BestDistance;
	}

	UFUNCTION(BlueprintPure, Category = "Score_cpp")
		int32 GetBestCoins() const
	{
		return BestCoins;
	}


	UFUNCTION(BlueprintPure, Category = "Score #cpp")
		float GetBestTime() const
	{
		return BestTime;
	}

};
