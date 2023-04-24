// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ScoreManager.h"

UScoreManager::UScoreManager()
{
	Score = 0;
}

void UScoreManager::AddScore(int32 ScoreToAdd)
{
	Score += ScoreToAdd;
}

int32 UScoreManager::GetScore() const
{
	return Score;
}

