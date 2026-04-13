// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TMMAPlayerState.generated.h"

#define DEFAULT_FIRST_EXTEND_SCORE 5000000; // 1回目のエクステンド点数
#define DEFAULT_EVERY_EXTEND_SCORE 20000000; // エブリエクステンド点数

/**
 * 
 */
class UTMMAGameInstanceBase; // 循環参照防止で…
class ATMMAPlayerController;

UCLASS()
class TESTMYMAKEACTION_API ATMMAPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	void TakeOverPlayerStatusToStage(UTMMAGameInstanceBase* InGameInstance);

	void SetPlayerStateByContinue(UTMMAGameInstanceBase* InGameInstance);

	void SetControllerByCast();

	ATMMAPlayerController* GetMainPlayerController()
	{
		return MainPlayerController;
	};

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

	void CheckExtendPlayer(bool& IsExtend);

	const int GetExtendCount() const
	{
		return ExtendCount;
	}

	const int GetNextExtendScore() const
	{
		return NextExtendScore;
	}

private:
	int Score;

	int Left;

	int ExtendCount = 0;

	int NextExtendScore = 5000000;

	ATMMAPlayerController* MainPlayerController;
};
