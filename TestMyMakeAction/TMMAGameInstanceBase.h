// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/AudioComponent.h"
#include "TMMAPlayerBase.h"
#include "DataAsset/Actor/TMMASoundManagerDataAsset.h"
#include "Object/TMMASoundManagerActor.h"
#include "TMMAGameInstanceBase.generated.h"

#define MAX_CREDIT_COUNT 9 // 最大追加可能クレジット数(9枚がデフォらしいので9で.)

/**
 * 
 */
// モード用列挙型
UENUM(BlueprintType)
enum class EBuildMode : uint8
{
	Development UMETA(DisplayName = "Development"), // 開発用
	Release UMETA(DisplayName = "Release"), // 製品用
	Portfolio UMETA(DisplayName = "Portfolio"), // ポートフォリオ用
	SNS UMETA (DisplayName = "SNS") // SNS上での投稿用 (Xなどで途中報告するときとか.)
};

// 言語モード
UENUM(BlueprintType)
enum class ELanguageMode : uint8
{
	Japanese UMETA(DisplayName="Japanese"),
	English UMETA(DisplayName="English")
};

// ランキング用プレイヤーステータス
USTRUCT(BlueprintType) 
struct FRankingPlayerStatus : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	// 順位
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerRankParam")
	int rank;
	// スコア
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerRankParam")
	int score;
	// プレイヤー名(3文字)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerRankParam")
	FString player_name;
	// 到達面(0はALL)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerRankParam")
	int stage;
};

USTRUCT(BlueprintType)
struct FGameSoundStruct
{
	GENERATED_USTRUCT_BODY()

	USoundBase* SoundBaseInstance;

	EGameSoundType SoundType = EGameSoundType::Stage;

	int IndexOfType; // サウンドタイプごとのインデックス値.
};

UCLASS()
class TESTMYMAKEACTION_API UTMMAGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int Player1Score;

	UPROPERTY()
	int GameHighScore;

	UPROPERTY()
	int Player1Left;

	UPROPERTY()
	int Player1Life = 100;

	UPROPERTY()
	int P1PowerLevel = 1;

	UPROPERTY()
	int P1LeftBurst = 3;

	UPROPERTY()
	int P1ExtendCount = 0;

	UPROPERTY()
	int P1NextExtendScore = 5000000;

	UPROPERTY()
	EShotType P1ShotType = EShotType::Rapid;

	UPROPERTY()
	int GameRank;

	UPROPERTY()
	int CurrentStage = 0;

	UPROPERTY()
	int ContinueCount;

	UPROPERTY()
	TArray<FRankingPlayerStatus> RankingPlayerStatuses;

	// プレイ終了までの一番良いスコアのプレイ履歴
	UPROPERTY()
	FRankingPlayerStatus PlayerTopStatus;

	// ランクインしているか
	bool IsRankIn = false;

	// ビルドモード
	UPROPERTY(EditAnywhere)
	EBuildMode BuildMode = EBuildMode::Development;

	// 言語設定(※後々メニュー経由で設定できるようにしておく)
	UPROPERTY()
	ELanguageMode LanguageMode = ELanguageMode::Japanese;

private:
	// ステージBGM
	UPROPERTY() // これを入れないとレベル遷移時にガベージコレクション行きで破棄されるのでつけること！！
	UAudioComponent* StageBgmComponent;

	TArray<FGameSoundStruct> SoundStructList;

	// 投入コイン
	UPROPERTY()
	int CoinCount;

	// クレジット
	UPROPERTY()
	int CreditCount;

	// 1クレジットにおける使用コイン数
	UPROPERTY()
	int UseCoinByCredit = 1;

public:
	// 一旦ゲーム用、ランキング用のプレイヤーステータスリセット
	UFUNCTION(BlueprintCallable)
	void InitPlayerGameAndRankingStatus();

	// ステータスをリセット
	UFUNCTION(BlueprintCallable)	
	void InitGameStatus(); 
	
	//	ステージクリア時のステータス設定
	UFUNCTION(BlueprintCallable)
	void StageClearGameStatusAndPlayerStatus(ATMMAGameStateBase* InGameStatus, ATMMAPlayerBase* InPlayer);

	// ミス時のプレイヤー設定
	UFUNCTION(BlueprintCallable)
	void MissPlayerState(ATMMAPlayerBase* InPlayerBase);

	// コンティニューでステータス継続
	UFUNCTION(BlueprintCallable)
	void ContinueGameStatus();

	// スコア関連
	UFUNCTION(BlueprintPure)
	int Get1PScore() {
		return Player1Score;
	}

	UFUNCTION(BlueprintCallable)
	void Set1PScore(int P1Score);

	UFUNCTION(BlueprintPure)
	int GetHighScore() {
		return GameHighScore;
	}

	UFUNCTION(BlueprintCallable)
	void SetHighScore(int InHighScore);

	// 残機関連
	UFUNCTION(BlueprintPure)
	int GetP1Left() {
		return Player1Left;
	}

	UFUNCTION(BlueprintCallable)
	void SetP1Left(int InP1Left);

	UFUNCTION(BlueprintCallable)
	void SetP1ExtendCount(int InP1ExtendCount);

	UFUNCTION(BlueprintPure)
	int GetP1ExtendCount() {
		return P1ExtendCount;
	}

	UFUNCTION(BlueprintCallable)
	void SetP1NextExtendScore(int InP1NextExtendScore);

	UFUNCTION(BlueprintPure)
	const int GetP1NextExtendScore() const
	{
		return P1NextExtendScore;
	}

	// ライフ関連
	UFUNCTION(BlueprintPure)
	int GetP1Life() {
		return Player1Life;
	}

	UFUNCTION(BlueprintCallable)
	void SetP1Life(int InP1Life);

	// プレイヤーキャラパワー関連
	UFUNCTION(BlueprintPure)
	int GetP1PowerLevel()
	{
		return P1PowerLevel;
	}

	UFUNCTION(BlueprintCallable)
	void SetP1PowerLevel(int InP1PowerLevel);

	UFUNCTION(BlueprintPure)
	EShotType GetP1ShotType() {
		return P1ShotType;
	}

	UFUNCTION(BlueprintCallable)
	void SetP1ShotType(EShotType InShotType);

	// バースト関連
	UFUNCTION(BlueprintPure)
	int GetP1LeftBurst() {
		return P1LeftBurst;
	}

	UFUNCTION(BlueprintCallable)
	void SetP1LeftBurst(int InBurstCount);

	// ゲームランク関連
	UFUNCTION(BlueprintCallable)
	void SetGameRank(int InGameRank);

	UFUNCTION(BlueprintPure)
	int GetGameRank() {
		return GameRank;
	}

	// ステージ関連
	UFUNCTION(BlueprintCallable)
	void SetCurrentStage(int InCurrentStage);

	UFUNCTION(BlueprintPure)
	const int GetCurrentStage() const {
		return CurrentStage;
	}

	UFUNCTION(BlueprintCallable)
	void SetStageBgmComponent(UAudioComponent* InStageBgmComponent);

	UFUNCTION(BlueprintPure)
	UAudioComponent* GetStageBgmComponent() const
	{
		return StageBgmComponent;
	}

	// ランキング関連
	UFUNCTION(BlueprintCallable)
	void SetInitRanking();

	UFUNCTION(BlueprintCallable)
	void InitPlayerRankStatus();

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString InPlayerName);

	UFUNCTION(BlueprintCallable)
	void CheckRankIn();

	UFUNCTION(BlueprintCallable)
	void RankIn();

	UFUNCTION(BlueprintPure)
	TArray<FRankingPlayerStatus> GetPlayerRankings() const {
		return RankingPlayerStatuses;
	}

	UFUNCTION(BlueprintPure)
	const int GetPlayerRankingsNum() const {
		return RankingPlayerStatuses.Num();
	}

	UFUNCTION(BlueprintCallable)
	void SavePlayerStatus();

	UFUNCTION(BlueprintPure)
	FRankingPlayerStatus GetPlayerTopStatus() const
	{
		return PlayerTopStatus;
	}

	UFUNCTION(BlueprintPure)
	const bool GetIsRankIn() const
	{
		return IsRankIn;
	}

	// サウンド関連
	// BGM再生
	void SpawnAndSetBgm(EGameSoundType InSoundType, int InIndexOfType);

	// フェードアウト
	void FadeOutBgm();

	// ストップ
	void StopBgm();

	// データアセット関連
	void SetSoudStructByDataAsset(UTMMASoundManagerDataAsset* InSoundDataAsset);

	FGameSoundStruct GetGameSoundStruct(EGameSoundType InSoundType, int InIndexOfType, bool& IsFinded) const
	{
		FGameSoundStruct ReturnSoundStruct;
		IsFinded = false;
		for (FGameSoundStruct SoundStruct : SoundStructList) {
			if (InSoundType == SoundStruct.SoundType && InIndexOfType == SoundStruct.IndexOfType) {
				// サウンドタイプとインデックス値の一致で取得.
				ReturnSoundStruct = SoundStruct;
				IsFinded = true;
				UE_LOG(LogTemp, Log, TEXT("finded game struct."));
				break;
			}
		}
		return ReturnSoundStruct;
	}

	// コイン関連
	void InsertCoin();

	void SetUseCoinByCredit(int InUseCoinByCredit);

	const int GetCoinCount() const
	{
		return CoinCount;
	}

	// クレジット関連

	void AddCredit();

	void UseCredit();

	const int GetCreditCount() const
	{
		return CreditCount;
	}
};
