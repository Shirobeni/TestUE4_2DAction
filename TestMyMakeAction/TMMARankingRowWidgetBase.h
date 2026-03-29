// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIBase.h"
#include "Components/TextBlock.h"
#include "TMMAGameInstanceBase.h"
#include "TMMARankingRowWidgetBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRankingParam 
{
	GENERATED_BODY()
	// 順位
	int rank;

	// スコアネーム
	FString name;

	// スコア
	int score;

	// 到達ステージ
	int stage;
};

UCLASS()
class TESTMYMAKEACTION_API UTMMARankingRowWidgetBase : public UGameUIBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetRankingParamAndText(int InRank, FString InName, int InScore, int InStage);

	UFUNCTION(BlueprintCallable)
	void SetRankingParamAndTextFromStatus(FRankingPlayerStatus RankingPlayerStatus);

public:

	FRankingParam RankingParam;

	// スコア用テキストブロック
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText = nullptr;


	// スコアネーム用テキストブロック
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* NameText = nullptr;


	// 順位用テキストブロック
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* RankText = nullptr;

	// 到達ステージ用テキストブロック
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* StageText = nullptr;


	
};
