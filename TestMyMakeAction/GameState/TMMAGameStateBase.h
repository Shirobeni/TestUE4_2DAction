// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "TestMyMakeAction/TMMAGameInstanceBase.h"
#include "TestMyMakeAction/Interface/TMMAGameStateInterface.h"
#include "TestMyMakeAction/PlayerState/TMMAPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "TMMAGameStateBase.generated.h"

#define DEFAULT_HIGH_SCORE 80000; // 初期ハイスコア
#define GAME_MODE_DEFAULT_FIRST_EXTEND_SCORE 5000000; // 1回目のエクステンド点数
#define GAME_MODE_DEFAULT_EVERY_EXTEND_SCORE 20000000; // エブリエクステンド点数
#define ALL_CLEAR_BASE_BONUS 10000000; // ALLクリアボーナス
#define ALL_CLEAR_LEFT_BONUS 3000000;

/**
 * 
 */
UENUM(BlueprintType)
enum class ECurrentStageEnum : uint8
{
	Stage1 UMETA(DisplayName = "Stage1"),
	Stage2 UMETA(DisplayName = "Stage2"),
	Stage3 UMETA(DisplayName = "Stage3"),
	Stage4 UMETA(DisplayName = "Stage4"),
	Stage5 UMETA(DisplayName = "Stage5"),
	Stage6 UMETA(DisplayName = "Stage6"),
	Stage7 UMETA(DisplayName = "Stage7")
};

UENUM(BlueprintType)
enum class ENavigationDirectEnum : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down")
};

UCLASS()
class TESTMYMAKEACTION_API ATMMAGameStateBase : public AGameStateBase, public IGameStateInterface
{
	GENERATED_BODY()
	

public:
	/* 複数マルチ関連 */
	//	面スタート時のステータス引継ぎ
	UFUNCTION(BlueprintCallable)
	void TakeOverStatusToStage(ATMMAPlayerBase* InPlayerActor, ECurrentStageEnum InCurrentStage);

	// クリア時の引継ぎ
	UFUNCTION(BlueprintCallable)
	void TakeStageClear();

	// コンティニュー時の引継ぎ
	UFUNCTION(BlueprintCallable)
	void SetStateContinue();

	/* スコア関連 */
	// ハイスコア
	UFUNCTION(BlueprintCallable)
	void UpdateHighScore();

	UFUNCTION(BlueprintCallable)
	void InitHighScore();

	UFUNCTION(BlueprintPure)
	const int GetHighScore() const
	{
		return HighScore;
	}

	UFUNCTION(BlueprintCallable)
	void AddAllClearBonus();
	
	// プレイヤー1スコア
	void SetP1Score(int InP1Score);

	void AddP1Score(int InAddP1Score);

	UFUNCTION(BlueprintPure)
	const int GetP1Score() const
	{
		return P1Score;
	}

	// 残機・エクステンド
	UFUNCTION(BlueprintCallable)
	void AddPlayerLeft(int InAddPlayerLeft);

	void SetLeft(int InP1Left);

	UFUNCTION(BlueprintPure)
	const int GetLeft() const
	{
		return P1Left;
	}

	UFUNCTION(BlueprintCallable)
	void AddP1ScoreByTime(int AddBaseScore, bool IsDiff, int InDiffParam);

	void ExtendPlayer(bool& IsExtend);

	void SetNextExtendScore(int InNextExtendScore);

	const int GetNextExtendScore() const
	{
		return P1NextExtendScore;
	}

	void SetExtendCount(int InExtendCount);

	const int GetExtendCount() const
	{
		return P1ExtendCount;
	}


	/* ステージ関連 */
	// 現在のステージ列挙
	UFUNCTION(BlueprintCallable)
	void SetCurrentStage(ECurrentStageEnum InCurrentStage);

	UFUNCTION(BlueprintPure)
	ECurrentStageEnum GetCurrentStage() const
	{
		return CurrentStage;
	}

	// 現在のステージ数
	UFUNCTION(BlueprintCallable)
	void SetCurrentStageNumByEnum();

	UFUNCTION(BlueprintPure)
	const int GetCurrentStageNum() const
	{
		return CurrentStageNum;
	}

	/* タイマー及びランク関連 */
	UFUNCTION(BlueprintCallable)
	void SetStageTime(float InLeftStageTime);

	UFUNCTION(BlueprintCallable)
	bool UpdateStageTime(float InDeltaSecods);

	void AddStageTime(float InAddDeltaSeconds);

	const int GetLeftStageTimeByConvertInt() const
	{
		return (int)LeftStageTime;
	}

	UFUNCTION(BlueprintCallable)
	void SetTimeLockFlag(bool InTimeLockFlag);

	void SetGameRank(int InGameRank);

	void AddGameRank(int InAddRank);

	UFUNCTION(BlueprintCallable)
	void UpdateTimerRank(float InAddTime);

	UFUNCTION(BlueprintPure)
	const int GetGameRank() const
	{
		return GameRank;
	}

	void AddDecreaseTimeFactor(float InDecreaseTimeFactor);

	// 進行方向
	UFUNCTION(BlueprintCallable)
	void SetNavigationDirect(ENavigationDirectEnum InNavigationDirect);

	UFUNCTION(BlueprintPure)
	ENavigationDirectEnum GetNavigationDirect() const
	{
		return NavigationDirect;
	}

	// 進行方向を左側へ出すフラグ
	UFUNCTION(BlueprintCallable)
	void SetLeftSideDirectionFlag(bool InLeftSideDirectionFlag);

	UFUNCTION(BlueprintPure)
	const bool GetLeftSideDirectionFlag() const
	{
		return LeftSideDirectionFlag;
	}

	/* その他 */
	// プレイヤーステート
	void SetP1PlayerState();

	ATMMAPlayerState* GetP1PlayerState() const
	{
		return P1PlayerState;
	}

	UFUNCTION(BlueprintCallable)
	void SetMainGameInstance(UTMMAGameInstanceBase* InMainGameInstance);

	UFUNCTION(BlueprintPure)
	UTMMAGameInstanceBase* GetMainGameInstance() const
	{
		return MainGameInstance;
	}

	UFUNCTION(BlueprintCallable)
	void SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode);

	UFUNCTION(BlueprintPure)
	ATestMyMakeActionGameModeBase* GetMainGameMode() const
	{
		return MainGameMode;
	}

private:
/*********************************************************
 *	ゲーム上関連
 **********************************************************/

	// ハイスコア
	int HighScore = 0;

	// ステージ残り時間
	float LeftStageTime = 100;

	// タイマー減少倍率
	float DecreaseTimeFactor = 1.0;

	// ゲームランク
	int GameRank = 1;

	// タイマーランク計測時間
	float RankTime = 0.0;

	// タイマー停止フラグ
	bool TimeLockFlag = false;

	// 現在のステージ
	ECurrentStageEnum CurrentStage;

	// 現在の面数
	int CurrentStageNum = 0;


	/*********************************************************
	 *	プレイヤー上関連
	 * ※現状1人用なのこちらで管理。2人用になったらPlayerStateで管理する予定
	 **********************************************************/
	 // 残機
	int P1Left = 2;

	// スコア
	int P1Score = 0;

	// プレイヤー1がスコアでエクステンドした回数。
	int P1ExtendCount = 0;

	// 次のエクステンド点数
	int P1NextExtendScore = 5000000;

	// 進行方向 ※ウィジェットのみ使用
	ENavigationDirectEnum NavigationDirect;
	
	// 進行方向を左側へ出すか
	bool LeftSideDirectionFlag = false;

	/*********************************************************
	 *	その他
	**********************************************************/
	// ゲームモード
	ATestMyMakeActionGameModeBase* MainGameMode;

	// プレイヤーステート(現状1Pのみ)
	ATMMAPlayerState* P1PlayerState;

	// ゲームインスタンス
	UTMMAGameInstanceBase* MainGameInstance;

};
