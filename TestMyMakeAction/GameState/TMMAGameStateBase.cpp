// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAGameStateBase.h"
#include "TestMyMakeAction/TMMAPlayerBase.h"
#include "TestMyMakeAction/TestMyMakeActionGameModeBase.h"
#include "TestMyMakeAction/TMMAMainGameWidgetBase.h"

// 面スタート時にインスタンス等からステータス引き継ぎ
void ATMMAGameStateBase::TakeOverStatusToStage(ATMMAPlayerBase* InPlayerActor, ECurrentStageEnum InCurrentStage)
{
	if (MainGameInstance != nullptr) {
		// TODO::ここら辺の処理はプレイヤーステートに移行するので、廃止予定
		P1Score = MainGameInstance->Get1PScore();
		P1Left = MainGameInstance->GetP1Left();
		UE_LOG(LogTemp, Log, TEXT("P1Left:%d"), MainGameInstance->GetP1Left());
		// -----------------------------------------------------------------

		P1PlayerState->SetScore(MainGameInstance->Get1PScore());
		P1PlayerState->SetLeft(MainGameInstance->GetP1Left());
		P1NextExtendScore = MainGameInstance->GetP1NextExtendScore();
		UE_LOG(LogTemp, Log, TEXT("P1NextExtendScore:%d"), MainGameInstance->GetP1NextExtendScore());
		P1ExtendCount = MainGameInstance->P1ExtendCount;
		CurrentStage = InCurrentStage;
		SetCurrentStageNumByEnum();
		MainGameInstance->SetCurrentStage(CurrentStageNum);
		if (InPlayerActor != nullptr) {
			InPlayerActor->SetShotLevel(MainGameInstance->GetP1PowerLevel());
		}
	}
	SetTimeLockFlag(false);
	DecreaseTimeFactor = 1.0f; // ステージ跨ぐので、タイマー減少倍率はリセットする.
//	if (MainGameMode != nullptr) {
//		MainGameMode->GetMainGameWidget()->UpdateLeft(P1Left);
//	}

}

//　クリア時の処理
void ATMMAGameStateBase::TakeStageClear() {
	AddP1ScoreByTime(20000, false, 0);
	AddGameRank(1);
	SetTimeLockFlag(true);
}

// コンティニュー時にゲームインスタンスから値をセット
void ATMMAGameStateBase::SetStateContinue()
{
	if (MainGameInstance != nullptr) {
		MainGameInstance->ContinueGameStatus();
		P1PlayerState->SetScore(MainGameInstance->Get1PScore());
		P1PlayerState->SetLeft(MainGameInstance->GetP1Left());
// TODO:: プレイヤーステート側に移行予定
		P1Score = MainGameInstance->Get1PScore();
//		AddP1Score(0); //TODO::いらんかも
		P1Left = MainGameInstance->GetP1Left();
// -------------------------------------
		P1NextExtendScore = DEFAULT_FIRST_EXTEND_SCORE;
	}
}


// ハイスコア更新
void ATMMAGameStateBase::UpdateHighScore()
{
	if (P1PlayerState->GetScore() > HighScore) {
		HighScore = P1PlayerState->GetScore();
	}
}

// ハイスコアの初期化
void ATMMAGameStateBase::InitHighScore()
{
	HighScore = DEFAULT_HIGH_SCORE;
}

// ALLクリアボーナス
void ATMMAGameStateBase::AddAllClearBonus()
{
	int GetBonus = ALL_CLEAR_BASE_BONUS;
	int LeftBonus = P1PlayerState->GetLeft() * ALL_CLEAR_LEFT_BONUS;
	GetBonus += LeftBonus;
	AddP1Score(GetBonus);
}

// プレイヤースコア設定
void ATMMAGameStateBase::SetP1Score(int InP1Score)
{
	P1Score = InP1Score;
}

// スコア加算
void ATMMAGameStateBase::AddP1Score(int InAddP1Score)
{
	if (!P1PlayerState) return;
	P1PlayerState->AddScore(InAddP1Score);
	P1Score += InAddP1Score; // TODO::後々廃止予定.
	// 加算のついでにハイスコア更新とエクステンドチェックを行う.
	UpdateHighScore();  // ハイスコア更新チェック
	bool IsExtend = false;
	ExtendPlayer(IsExtend); // エクステンドチェック.
}

// 残り時間によるスコア加算
void ATMMAGameStateBase::AddP1ScoreByTime(int AddBaseScore, bool IsDiff, int InDiffParam)
{
	int AddScore = 0;
	if (IsDiff == true && InDiffParam > 0) {
		AddScore = AddBaseScore * floor(LeftStageTime / InDiffParam);
	}
	else {
		AddScore = AddBaseScore * floor(LeftStageTime);
	}
	AddP1Score(AddScore); // TODO::プレイヤーステート以降により、廃止予定.
	P1PlayerState->AddScore(AddScore);
}

//	残機数設定
void ATMMAGameStateBase::SetLeft(int InP1Left)
{
	P1Left = InP1Left;
}

// 残機数更新(引数は追加前提、減らすときは-の値に)
void ATMMAGameStateBase::AddPlayerLeft(int InAddPlayerLeft)
{
	P1Left += InAddPlayerLeft;
}

// エクステンド
void ATMMAGameStateBase::ExtendPlayer(bool& IsExtend)
{
	bool IsExtendFlag = false;
	if (P1PlayerState) {
		int Player1Score = P1PlayerState->GetScore();
		if (Player1Score >= P1NextExtendScore) {
			UE_LOG(LogTemp, Log, TEXT("NowExtend...=%d"), P1NextExtendScore);
			UE_LOG(LogTemp, Log, TEXT("Player1Score to ExtendTiming...=%d"), Player1Score);
			P1Left++;
			P1ExtendCount++;
			int NewNextExtendScore = P1ExtendCount * DEFAULT_EVERY_EXTEND_SCORE;
			SetNextExtendScore(NewNextExtendScore);
			UE_LOG(LogTemp, Log, TEXT("NextExtend...=%d"), P1NextExtendScore);
			IsExtendFlag = true;
			if (MainGameMode != nullptr) {
				MainGameMode->GetMainGameWidget()->UpdateLeft(P1Left);
			}
		}
	}
	IsExtend = IsExtendFlag;
}

// 次のエクステンド点数の設定
void ATMMAGameStateBase::SetNextExtendScore(int InNextExtendScore) 
{
	P1NextExtendScore = InNextExtendScore;
}

// エクステンド回数の設定
void ATMMAGameStateBase::SetExtendCount(int InExtendCount)
{
	P1ExtendCount = InExtendCount;
}
// 現在のステージの設定
void ATMMAGameStateBase::SetCurrentStage(ECurrentStageEnum InCurrentStage)
{
	CurrentStage = InCurrentStage;
}

// 現在のステージをステージ数にコンバートして設定
void ATMMAGameStateBase::SetCurrentStageNumByEnum()
{
	CurrentStageNum = 0;
	switch (CurrentStage) {
		case ECurrentStageEnum::Stage1:
			CurrentStageNum = 1;
			break;
		case ECurrentStageEnum::Stage2:
			CurrentStageNum = 2;
			break;
		case ECurrentStageEnum::Stage3:
			CurrentStageNum = 3;
			break;
		case ECurrentStageEnum::Stage4:
			CurrentStageNum = 4;
			break;
		case ECurrentStageEnum::Stage5:
			CurrentStageNum = 5;
			break;
		case ECurrentStageEnum::Stage6:
			CurrentStageNum = 6;
			break;
		case ECurrentStageEnum::Stage7:
			CurrentStageNum = 7;
			break;
		default:
			break;
	}
}

// 残り時間の設定
void ATMMAGameStateBase::SetStageTime(float InLeftStageTime)
{
	LeftStageTime = InLeftStageTime;
}

// 残り時間増加
void ATMMAGameStateBase::AddStageTime(float InAddDeltaSeconds)
{
	LeftStageTime += InAddDeltaSeconds;
}


// 残り時間の更新
bool ATMMAGameStateBase::UpdateStageTime(float InDeltaSecods)
{
	bool ReturnFlag = false;
	if (TimeLockFlag == false) {
		float LaterStageTime = LeftStageTime - (InDeltaSecods * DecreaseTimeFactor);
		if (LaterStageTime < 0) {
			LeftStageTime = 100.0;
			ReturnFlag = true;
		}
		else {
			LeftStageTime = LaterStageTime;
		}
	}
	return ReturnFlag;
}

// タイマーロックフラグの設定
void ATMMAGameStateBase::SetTimeLockFlag(bool InTimeLockFlag)
{
	TimeLockFlag = InTimeLockFlag;
}

// タイマー減少倍率の加算
void ATMMAGameStateBase::AddDecreaseTimeFactor(float InDecreaseTimeFactor)
{
	DecreaseTimeFactor += InDecreaseTimeFactor;
}

// ランク値設定
void ATMMAGameStateBase::SetGameRank(int InGameRank)
{
	GameRank = InGameRank;
}

// ランク上昇
void ATMMAGameStateBase::AddGameRank(int InAddRank)
{
	GameRank += InAddRank;
}

// タイマーランク
void ATMMAGameStateBase::UpdateTimerRank(float InAddTime)
{
	RankTime += InAddTime;
	if (RankTime >= 200.0) {
		RankTime = 0.0;
		AddGameRank(1);
		UE_LOG(LogTemp, Warning, TEXT("output : %s"), L"RANK_UPDATE");
	}
}

// 進行方向の設定
void ATMMAGameStateBase::SetNavigationDirect(ENavigationDirectEnum InNavigationDirect)
{
	NavigationDirect = InNavigationDirect;
}

// 進行方向を左側へ出すフラグの設定
void ATMMAGameStateBase::SetLeftSideDirectionFlag(bool InLeftSideDirectionFlag)
{
	LeftSideDirectionFlag = InLeftSideDirectionFlag;
}

//プレイヤー1用プレイヤーステート設定
void ATMMAGameStateBase::SetP1PlayerState()
{
	// 一応null及びvalidationチェック.
	if (!PlayerArray[0]) return;
	if (ATMMAPlayerState* CastedP1PlayerState = Cast<ATMMAPlayerState>(PlayerArray[0])) {
		P1PlayerState = CastedP1PlayerState;
	}
}

// インスタンスの設定
void ATMMAGameStateBase::SetMainGameInstance(UTMMAGameInstanceBase* InMainGameInstance)
{
	MainGameInstance = InMainGameInstance;
}

// ゲームモードの設定
void ATMMAGameStateBase::SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode)
{
	MainGameMode = InMainGameMode;
}