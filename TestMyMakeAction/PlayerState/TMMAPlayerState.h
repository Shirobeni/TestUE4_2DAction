// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TMMAPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void SetScore(int InScore);

	void AddScore(int InAddedScore);

	const int GetScore() const
	{
		return Score;
	}

	void SetLeft(int InLeft);

	void ChangeLeft(bool IsExtend);

	const int GetLeft() const
	{
		return Left;
	}


private:
	int Score;

	int Left;
};
