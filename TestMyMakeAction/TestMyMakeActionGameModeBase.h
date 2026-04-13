// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TMMAGameInstanceBase.h"
#include "ContinueWidget.h"
#include "TMMAGameOverWidget.h"
#include "TMMAPlayerBase.h"
#include "TMMAPlayerCameraBase.h"
#include "TMMAWidgetControllPawn.h"
#include "TMMAGameModeInterface.h"
#include "TestMyMakeAction/GameState/TMMAGameStateBase.h"
#include "TestMyMakeActionGameModeBase.generated.h"

#define FIX_X_VECTOR_FOR_PLAYER -69.0;

class UTMMAMaingameWidget;

UENUM(BlueprintType)
enum class EPlayerMissType : uint8
{
	Defeated UMETA(DisplayName = "Defeated"),
	DropOut UMETA(DisplayName = "DropOut")
};

UENUM(BlueprintType)
enum class ECurrentStage : uint8
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
enum class ECurrentGameMode : uint8
{
	Action UMETA(DisplayName = "Action"),
	Shooting UMETA(DisplayName = "Shooting")
};

UENUM(BlueprintType)
enum class ENavigationDirect : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTMYMAKEACTION_API ATestMyMakeActionGameModeBase : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()


public:
	// 開始時の処理.
	virtual void BeginPlay() override;

	/**
	 * 各ウィジェット設定
	 */
	UFUNCTION(BlueprintCallable)
	void SetWidgetBySubclass();

	/**
	 * メインウィジェット設定
	 */ 
	// 生成したウィジェットクラスから
	UFUNCTION(BlueprintCallable)
	void SetMainGameWidget(UTMMAMaingameWidgetBase* InMainGameWidget);

	UFUNCTION(BlueprintPure)
	UTMMAMaingameWidgetBase* GetMainGameWidget() {
		return MainGameWidget;
	}

	//複数マルチ関連
	// ステージ開始時の設定
	void InitializeStage(ECurrentStageEnum InCurrentStageEnum);
	
	//ステージクリア
	UFUNCTION(BlueprintCallable)
	void TakeStageClear();

	// 次のレベル(ステージ)の非同期読み込み
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();

	// 次のレベル(ステージ)を開く
	void ExecuteOpenNextLevel();

	void OpenNextLevel();

	// ALLクリア時の残機、残バーストボーナス加算
	// TODO::処理面含めて後々実装予定
//	UFUNCTION(BlueprintCallable)
//	void convertToScoreForLeftAndBurst(int InLeft, int InBurst);

	UFUNCTION(BlueprintCallable)
	void RestartPlayerAndCamera();

	// ゲームインスタンス関連
	UFUNCTION(BlueprintCallable)
	void SetMainGameInstance(UTMMAGameInstanceBase* InGameInstance);


	UFUNCTION(BlueprintPure)
	UTMMAGameInstanceBase* GetMainGameInstance() const
	{
		return MainGameInstance;
	}

	// ゲームステート関連
	UFUNCTION(BlueprintCallable)
	void SetMainGameState(ATMMAGameStateBase* InMainGameState);

	UFUNCTION(BlueprintPure)
	ATMMAGameStateBase* GetMainGameState() const
	{
		return MainGameState;
	}

	// ミス関連
	UFUNCTION(BlueprintCallable)
	void PlayerMiss(EPlayerMissType InPlayerMissType);

	void TimerMissFunc();

	UFUNCTION(BlueprintCallable)
	void SequenceAfterMiss();

	UFUNCTION(BlueprintCallable)
	void Continue();

	UFUNCTION(BlueprintCallable)
	void ViewContinueScreen(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void ContinuePlayerStatus(UTMMAGameInstanceBase* InGameInstance, ATMMAPlayerBase* InPlayerActor);

	// 残り時間関係
	UFUNCTION(BlueprintCallable)
	bool UpDateStageTime(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	bool UpdateStageTimeAndText(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	void AddStageTime(float AddTime);

	UFUNCTION(BlueprintCallable)
	void SetStageTime(float InLeftStageTime);

	UFUNCTION(BlueprintPure)
	float GetLeftStageTime() {
		return LeftStageTime;
	}

	UFUNCTION(BlueprintCallable)
	void SetIsLockTimer(bool InIsLockTimer);

	UFUNCTION(BlueprintPure)
	bool GetIsLockTimer() {
		return IsLockTimer;
	}


		
	// ゲームランク関係
	UFUNCTION(BlueprintCallable)
	void InitializeGameRank();

	UFUNCTION(BlueprintCallable)
	void UpdateGameRank(int AddRank);

	UFUNCTION(BlueprintCallable)
	void TimerRank(float AddTime);

	UFUNCTION(BlueprintCallable)
	void SetGameRank(int InRank);

	UFUNCTION(BlueprintPure)
	int GetGameRank() {
		return GameRank;
	}
	
	// ミス関連

	UFUNCTION(BlueprintCallable)
		void SetPlayerMissType(EPlayerMissType InPlayerMissType);


	UFUNCTION(BlueprintPure)
	EPlayerMissType GetPlayerMissType() {
		return PlayerMissType;
	}


	// プレイヤー(及びそのカメラ)関連
	UFUNCTION(BlueprintCallable)
	void SetControllPlayer(ATMMAPlayerBase* InControllPlayer);

	UFUNCTION(BlueprintCallable)
	void SetPlayerAndCamera(ATMMAPlayerBase*& SpawnedPlayer);

	UFUNCTION(BlueprintPure)
	ATMMAPlayerBase* GetControllPlayer()
	{
		return ControllPlayer;
	}


	UFUNCTION(BlueprintCallable)
	void RespawnPlayer(ATMMAPlayerBase*& SpawnedPlayer);

	UFUNCTION(BlueprintCallable)
	void SetPlayerCamera(ATMMAPlayerCameraBase* InPlayerCamera);

	void SetPlayerCamerBySoftClass();

	UFUNCTION(BlueprintPure)
	ATMMAPlayerCameraBase* GetPlayerCamera() const
	{
		return PlayerCamera;
	}

	//ボスバトル関連
	UFUNCTION(BlueprintCallable)
	void SetIsBossBattle(bool InIsBossBattle);

	UFUNCTION(BlueprintPure)
	const bool GetIsBossBattle() const
	{
		return IsBossBattle;
	}

	UFUNCTION(BlueprintCallable)
	void SetIsStageBossBattle(bool InIsStageBossBattle);

	UFUNCTION(BlueprintPure)
	const bool GetIsStageBossBattle() const
	{
		return IsStageBossBattle;
	}

	UFUNCTION(BlueprintCallable)
		void SetRestartPointByActor();

	UFUNCTION(BlueprintPure)
		FTransform GetRestartPoint()
	{
		return RestartPoint;
	}

	// ZKill用スタートポイント格納
	void SetZkillStartPointArray();

	UFUNCTION(BlueprintCallable)
	void HouseZkillStartPointArray(AActor* InZKillStartPoint);

	UFUNCTION(BlueprintPure)
		TArray<AActor*> GetZkillStartPointArray() {
		return ZkillStartPointArray;
	}

	UFUNCTION(BlueprintCallable)
		void SetBossLockColision(AActor* InBossLockColition);

	UFUNCTION(BlueprintPure)
		AActor* GetBossLockColision() {
		return BossLockColision;
	}

	//	ステージ関連
	UFUNCTION(BlueprintCallable)
		void SetCurrentStage(ECurrentStage InCurrentStage);

	UFUNCTION(BlueprintPure)
		const ECurrentStage GetCurrentStage() const
	{
		return CurrentStage;
	}

	UFUNCTION(BlueprintPure)
	const int GetCurrentStageNum() const {
		int StageNum = 0;
		switch (CurrentStage) {
			case ECurrentStage::Stage1:
				StageNum = 1;
				break;
			case ECurrentStage::Stage2:
				StageNum = 2;
				break;
			case ECurrentStage::Stage3:
				StageNum = 3;
				break;
			case ECurrentStage::Stage4:
				StageNum = 4;
				break;
			case ECurrentStage::Stage5:
				StageNum = 5;
				break;
			case ECurrentStage::Stage6:
				StageNum = 6;
				break;
			case ECurrentStage::Stage7:
				StageNum = 7;
				break;
			default:
				break;
		}
		return StageNum;
	}

	UFUNCTION(BlueprintCallable)
	void ConvertCurrentStageToInt(int& CurrentStageInt);

	UFUNCTION(BlueprintCallable)
	void SetGoalBossLockCollision(AActor* InGoalBossLockCollision);

	UFUNCTION(BlueprintCallable)
	void SetGoalBossLockCollisionByClass();

	UFUNCTION(BlueprintCallable)
	void CheckPenaltyDistanceGoalToPlayer();

	UFUNCTION(BlueprintCallable)
		void SetIsClear(bool InIsClear);

	UFUNCTION(BlueprintPure)
		const bool GetIsClear() const
	{
		return IsClear;
	}

	UFUNCTION(BlueprintCallable)
	void SetCurrentGameMode(ECurrentGameMode InCurrentGameMode);

	UFUNCTION(BlueprintPure)
	const ECurrentGameMode GetCurrentGameMode () const
	{
		return CurrentGameMode;
	}

	// BGM関連
	// ステージBGM
	void SpawnAndPlayStageBGM(int InIndexOfSoundType);
	
	// ボスBGM
	UFUNCTION(BlueprintCallable)
	void SpawnAndPlayBossBGM(int InIndexOfSoundType);

	// TODO::下記2つ恐らく廃止予定.
	UFUNCTION(BlueprintCallable)
	void SetStageBgmComponent(UAudioComponent* InStageBgmComponent);

	UFUNCTION(BlueprintPure)
	UAudioComponent* GetStageBgmComponent() const
	{
		return StageBgmComponent;
	}


	// ナビゲーション関連
	UFUNCTION(BlueprintCallable)
	void SetNavigationDirect(ENavigationDirect InNavigationDirect);

	UFUNCTION(BlueprintPure)
	ENavigationDirect GetNavigationDirect() const
	{
		return NavigationDirect;
	}

	UFUNCTION(BlueprintCallable)
	void SetIsDirectLeftSide(bool InIsDirectLeftSide);

	UFUNCTION(BlueprintPure)
	const bool GetIsDirectLeftSide() const
	{
		return IsDirectLeftSide;
	}

	UFUNCTION(BlueprintCallable)
	void ViewNavigation();

	// ウィジェット操作用ポーン関連
	void SpawnWidgetControllPawnBySoftClass();

	UFUNCTION(BlueprintCallable)
	void SetWidgetControllPawn(ATMMAWidgetControllPawn* InContinueControllPawn);

	UFUNCTION(BlueprintPure)
	ATMMAWidgetControllPawn* GetWidgetControllPawn() const{
		return WidgetControllPawn;
	}

	// コンティニュー関連
	UFUNCTION(BlueprintCallable)
	void SetContinueWidget(UContinueWidget* InContinueWidget);

	UFUNCTION(BlueprintPure)
	UContinueWidget* GetContinueWidget() const {
		return ContinueWidget;
	}

	UFUNCTION(BlueprintCallable)
	void SetContinueWidgetAndControllPawn(UContinueWidget* InContinueWidget, ATMMAWidgetControllPawn* InContinueControllPawn);

	// ゲームオーバー関連
	UFUNCTION(BlueprintCallable)
	void SetGameOverWidget(UTMMAGameOverWidget* InGameOverWidget);

	UFUNCTION(BlueprintPure)
	UTMMAGameOverWidget* GetGameOverWidget() const {
		return GameOverWidget;
	}

public:
	/*********************************************************
	 *		プレイヤー関連
	 **********************************************************/
	// 現在操作中のプレイヤー
	ATMMAPlayerBase* ControllPlayer;

	// プレイヤー1スコア
	int Player1Score = 0;

	// プレイヤー用カメラ
	// 先にクラスから取得.
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<ATMMAPlayerCameraBase> SoftCameraClass;

	ATMMAPlayerCameraBase* PlayerCamera;

	// アクション用プレイヤークラス
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATMMAPlayerBase> ActionPlayerClass;

	// シューティング用プレイヤークラス
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATMMAPlayerBase> ShootingPlayerClass;

	// ゲームオーバー時のダミー用プレイヤークラス
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATMMAPlayerBase> DummyPlayerClass;

	// ZKillによる落下後の復帰判定用クラス,
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<AActor> SoftZkillStartClass;

	/**********************************************************/


	/*********************************************************
	 *		ゲームステート関連 TODO:: 一部はTMMAGameStateBaseへ引っ越し
	 **********************************************************/
	// ハイスコア
	int HighScore = 80000;

	// ステージ残り時間
	float LeftStageTime = 100;

	// タイマー減少倍率
	float DecreaseTimeFactor = 1.0;

	// 残機
	int Player1Left = 2;

	// プレイヤー1がスコアでエクステンドした回数。
	int P1ExtendCount = 0;

	int P1NextExtendScore = 5000000;

	// ゲームランク
	int GameRank = 1;

	// タイマーランク計測時間
	float RankTime = 0.0;

	// 現在のステージ
		ECurrentStage CurrentStage = ECurrentStage::Stage1;

	// プレイヤーミス種類
		EPlayerMissType PlayerMissType = EPlayerMissType::Defeated;

	// 現在のゲームモード
		ECurrentGameMode CurrentGameMode = ECurrentGameMode::Action;
	
	// ボスフラグ
		bool IsBossBattle = false;

	// ステージボスフラグ
		bool IsStageBossBattle = false;

	// クリアフラグ
		bool IsClear = false;

	// 設定されている方向ナビ
		ENavigationDirect NavigationDirect = ENavigationDirect::Right;

	// リスタートポイント
		FTransform RestartPoint;

	// 落下時の復帰ポイント
		TArray<AActor*> ZkillStartPointArray;

	// ゴール用ボスロックコリジョン
		UPROPERTY(EditDefaultsOnly)
		TSoftClassPtr<AActor> SoftBossLockCollision;

	// ボス時のカメラ固定コリジョン
		AActor* BossLockColision;

	// ゴールとなるボスコリジョン
		AActor* GoalBossLockCollision;

	// ゴールとプレイヤーキャラの距離
		float DistancePlayerAndGoal = 999999.9;

	// ↑の最小距離
		float MinDistancePlayerAndGoal = 999999.9;

	// ペナルティカウント(ずっとその場で進まなかったり、立ち止まったりしないようにするため.　カウント超えたらランク上昇、タイマー減少時間加速)
		int PenaltyCount = 0;
	
	// ↑のボーダー
		int BorderPenaltyCount = 700;

	// ゲームBGM
		UAudioComponent* StageBgmComponent;

	// ゲームステート
		ATMMAGameStateBase* MainGameState;

	// ゲームインスタンス
		UTMMAGameInstanceBase* MainGameInstance;

	/**********************************************************/

	/*********************************************************
	 *		ウィジェット関連
	 **********************************************************/
	// メインゲームUIのウィジェット
		// サブクラス
		UPROPERTY(EditDefaultsOnly)
		TSoftClassPtr<UTMMAMaingameWidgetBase> MainGameWidgetSoftClass;

		// Object
		UTMMAMaingameWidgetBase* MainGameWidget;

	// コンティニュー用ウィジェット
		// サブクラス 
		UPROPERTY(EditDefaultsOnly)
		TSoftClassPtr<UContinueWidget> ContinueWidgetSoftClass;
		// Object
		UContinueWidget* ContinueWidget;

	// ゲームオーバー用ウィジェット
		UPROPERTY(EditDefaultsOnly)
		TSoftClassPtr<UTMMAGameOverWidget> GameOverWidgetSoftClass;

		UTMMAGameOverWidget* GameOverWidget;

	// コンティニュー時に使用するウィジェット入力用ポーン
		// 参照用ソフトクラス
		UPROPERTY(EditDefaultsOnly)
		TSoftClassPtr<ATMMAWidgetControllPawn> SoftWidgetControllPawnClass;

		ATMMAWidgetControllPawn* WidgetControllPawn;
	/**********************************************************/

protected:
	// 進行方向を左側に出すかのフラグ
	bool IsDirectLeftSide = false;


private:
	bool IsLockTimer = false;

};
