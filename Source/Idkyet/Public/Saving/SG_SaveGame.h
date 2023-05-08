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
};
