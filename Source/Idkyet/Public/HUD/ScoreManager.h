// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScoreManager.generated.h"

/**
 * 
 */
UCLASS()
class IDKYET_API UScoreManager : public UObject
{
	GENERATED_BODY()
	
public:
	UScoreManager();
	void AddScore(int32 ScoreToAdd);
	int32 GetScore() const;

private:
	int32 Score;
};
