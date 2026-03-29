// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIBase.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TMMANameRegistWidget.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FRegistCharacter
{
	GENERATED_BODY()

	FString character;

	int index;
};


UCLASS()
class TESTMYMAKEACTION_API UTMMANameRegistWidget : public UGameUIBase
{
	GENERATED_BODY()


public:
	// ネームレジスト時間初期化
	UFUNCTION(BlueprintCallable)
	void InitNameRegistCountAndComma();

	UFUNCTION(BlueprintCallable)
	void ReduceNameRegistTime();

	UFUNCTION(BlueprintPure)
	const int GetNameRegistCount() const
	{
		return NameRegistCount;
	}

	UFUNCTION(BlueprintCallable)
	void SetIsCompleteRegist(bool InIsCompleteRegist);

	UFUNCTION(BlueprintPure)
	const bool GetIsCompleteRegist() const
	{
		return IsCompleteRegist;
	}

	// スコアとランクを設定
	UFUNCTION(BlueprintCallable)
	void SetScoreAndRankText(int InRank, int InScore);

	//ステージを設定
	UFUNCTION(BlueprintCallable)
	void SetStageText(int InStage);

	UFUNCTION(BlueprintCallable)
	void InitRegistCharacters();

	// 選択中の文字を設定
	UFUNCTION(BlueprintCallable)
	void SetSelectRegistCharacter(int InIndex);

	// 文字選択
	UFUNCTION(BlueprintCallable)
	void MoveAndGetRegistCharacter(int AddIndex, FString& ReturnCharacter);

	// 文字選択からテキストセットまで.
	UFUNCTION(BlueprintCallable)
	void MoveAndGetRegistCharacterByTextBlock(int AddIndex, UTextBlock* InTextBlock, FString& ReturnCharacter);

	// プレイヤーネーム作成
	UFUNCTION(BlueprintCallable)
	void CreatePlayerName(FString& PlayerName);

	// 選択中の文字を取得
	UFUNCTION(BlueprintPure)
	const FRegistCharacter GetSelectRegistCharacter() const
	{
		return SelectRegistCharacter;
	}

	UFUNCTION(BlueprintPure)
	const TArray <FRegistCharacter> GetRegistCharacters() const
	{
		return RegistCharacters;
	}

	UFUNCTION(BlueprintCallable)
	void AddSelectNameTextNo(int AddNo);

	UFUNCTION(BlueprintPure)
	const int GetSelectNameTextNo() const
	{
		return SelectNameTextNo;
	}
	

	// テキスト関連
	UFUNCTION(BlueprintPure)
	UTextBlock* GetFirstText() const
	{
		return FirstText;
	}

	UFUNCTION(BlueprintPure)
	UTextBlock* GetSecondText() const
	{
		return SecondText;
	}

	UFUNCTION(BlueprintPure)
	UTextBlock* GetThridText() const
	{
		return ThirdText;
	}

	UFUNCTION(BlueprintPure)
	UTextBlock* GetNameTextBySelectNo() const {
		UTextBlock* ReturnTextBlock = nullptr;
		switch (SelectNameTextNo)
		{
		case 1:
			if (FirstText != nullptr) {
				ReturnTextBlock = FirstText;
			}
			break;
		case 2:
			if (SecondText != nullptr) {
				ReturnTextBlock = SecondText;
			}
			break;
		case 3:
			if (ThirdText != nullptr) {
				ReturnTextBlock = ThirdText;
			}
			break;
		default:
			break;
		}
		return ReturnTextBlock;
	}

public:
	// ネームレジスト文字一覧
	TArray<FRegistCharacter> RegistCharacters;

	// 選択中の文字情報.
	FRegistCharacter SelectRegistCharacter;

	int SelectNameTextNo = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NameRegistComma")
	float NameRegistComma = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NameRegistCount")
	int NameRegistCount = 30;

	bool IsCompleteRegist = false;

	// スコア用テキストブロック
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText = nullptr;

	// 順位用テキストブロック
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* RankText = nullptr;

	// 到達ステージ用テキストブロック
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* StageText = nullptr;

	// それぞれ1～3文字目.
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* FirstText = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* SecondText = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ThirdText = nullptr;

};
