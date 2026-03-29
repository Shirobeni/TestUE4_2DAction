// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAGameInstanceBase.h"
#include "TestMyMakeActionGameModeBase.h"
#include "TestMyMakeAction/GameState/TMMAGameStateBase.h"
#include "Object/TMMACustomWorldSettings.h"


void UTMMAGameInstanceBase::InitPlayerGameAndRankingStatus()
{
	InitGameStatus();
	InitPlayerRankStatus();
}

void UTMMAGameInstanceBase::InitGameStatus() {
	Player1Left = 2;
	Player1Score = 0;
	GameRank = 0;
	P1PowerLevel = 1;
	P1ShotType = EShotType::Rapid;
	ContinueCount = 0;
	IsRankIn = false;
}

void UTMMAGameInstanceBase::StageClearGameStatus(ATestMyMakeActionGameModeBase* InGameMode, ATMMAPlayerBase* InPlayer)
{
	// TODO::必要なければ廃止予定.
	Set1PScore(InGameMode->GetP1Score());
	SetP1Left(InGameMode->GetPlayer1Left());
	SetHighScore(InGameMode->GetHighScore());
	SetGameRank(InGameMode->GetGameRank());
//	SetStageBgmComponent(StageBgmComponent);
	SetP1ExtendCount(InGameMode->GetP1ExtendCount());
	SetP1NextExtendScore(InGameMode->GetP1NextExtendScore());
	SetP1Life(InPlayer->GetPlayerLife());
	SetP1PowerLevel(InPlayer->GetShotLevel());
	SetP1ShotType(InPlayer->GetShotType());
	SetP1LeftBurst(InPlayer->GetBurstCount());
}

void UTMMAGameInstanceBase::StageClearGameStatusAndPlayerStatus(ATMMAGameStateBase* InGameStatus, ATMMAPlayerBase* InPlayer)
{
	Set1PScore(InGameStatus->GetP1Score());
	SetP1Left(InGameStatus->GetLeft());
	UE_LOG(LogTemp, Log, TEXT("left in instance:%d"), Player1Left);
	SetHighScore(InGameStatus->GetHighScore());
	SetGameRank(InGameStatus->GetGameRank());
	SetP1ExtendCount(InGameStatus->GetExtendCount());
	SetP1NextExtendScore(InGameStatus->GetNextExtendScore());
	UE_LOG(LogTemp, Log, TEXT("next extend score by instance:%d"), InGameStatus->GetNextExtendScore());
	UE_LOG(LogTemp, Log, TEXT("next extend score instance:%d"), P1NextExtendScore);
	SetP1Life(InPlayer->GetPlayerLife());
	SetP1PowerLevel(InPlayer->GetShotLevel());
	SetP1ShotType(InPlayer->GetShotType());
	SetP1LeftBurst(InPlayer->GetBurstCount());
	UE_LOG(LogTemp, Log, TEXT("StageClearGameStatusAndPlayerStatus OK."));
}


void UTMMAGameInstanceBase::MissPlayerState(ATMMAPlayerBase* InPlayerBase)
{
	SetP1PowerLevel(InPlayerBase->GetShotLevel() - 1);
	SetP1ShotType(InPlayerBase->GetShotType());
	SetP1LeftBurst(3);
	SetP1Life(100);
	UE_LOG(LogTemp, Log, TEXT("UTMMAGameInstance::MissPlayerState() Completed"));
}

void UTMMAGameInstanceBase::ContinueGameStatus() {
	ContinueCount++;
	Player1Left = 2;
	Player1Score = ContinueCount;
	GameRank = 0;
	P1PowerLevel = 1;
	P1ShotType = EShotType::Rapid;
}

void UTMMAGameInstanceBase::Set1PScore(int P1Score)
{
	Player1Score = P1Score;
	UE_LOG(LogTemp, Log, TEXT("UTMMAGameInstance::Set1PScore() Completed"));
}

void UTMMAGameInstanceBase::SetHighScore(int InHighScore)
{
	GameHighScore = InHighScore;
}

void UTMMAGameInstanceBase::SetGameMode(ATestMyMakeActionGameModeBase* InGameMode)
{
	GameMode = InGameMode;
}

void UTMMAGameInstanceBase::SetP1Left(int InP1Left)
{
	Player1Left = InP1Left;
}

void UTMMAGameInstanceBase::SetP1ExtendCount(int InP1ExtendCount)
{
	P1ExtendCount = InP1ExtendCount;
}

void  UTMMAGameInstanceBase::SetP1NextExtendScore(int InP1NextExtendScore)
{
	P1NextExtendScore = InP1NextExtendScore;
}

void UTMMAGameInstanceBase::SetP1Life(int InP1Life)
{
	Player1Life = InP1Life;
}

void UTMMAGameInstanceBase::SetP1PowerLevel(int InP1PowerLevel)
{
	P1PowerLevel = InP1PowerLevel;
}

void UTMMAGameInstanceBase::SetP1ShotType(EShotType InShotType)
{
	P1ShotType = InShotType;
}

void UTMMAGameInstanceBase::SetP1LeftBurst(int InBurstCount)
{
	P1LeftBurst = InBurstCount;
}

void UTMMAGameInstanceBase::SetGameRank(int InGameRank)
{
	GameRank = InGameRank;
}

void UTMMAGameInstanceBase::SetCurrentStage(int InCurrentStage)
{
	CurrentStage = InCurrentStage;
}

void UTMMAGameInstanceBase::SetStageBgmComponent(UAudioComponent* InStageBgmComponent)
{
	StageBgmComponent = InStageBgmComponent;
}

void UTMMAGameInstanceBase::InitPlayerRankStatus()
{
	PlayerTopStatus.score = 0;
	PlayerTopStatus.stage = 1;
	PlayerTopStatus.rank = 9999;
	PlayerTopStatus.player_name = "";

}

void UTMMAGameInstanceBase::SetInitRanking()
{
	if (RankingPlayerStatuses.Num() < 5) {
		// テーブルで初期値設定できるかもしれないけど一応
		for (int i = 0; i < 5; i++) {
			FRankingPlayerStatus DefaultRankingPlayerStatus;
			DefaultRankingPlayerStatus.rank = i + 1;
			DefaultRankingPlayerStatus.stage = 1;
			DefaultRankingPlayerStatus.score = 80000 - (i * 5000);
			DefaultRankingPlayerStatus.player_name = "...";
			RankingPlayerStatuses.Add(DefaultRankingPlayerStatus);
		}
	}
}

void UTMMAGameInstanceBase::SetPlayerName(FString InPlayerName)
{
	PlayerTopStatus.player_name = InPlayerName;
}

void UTMMAGameInstanceBase::CheckRankIn() {
	UE_LOG(LogTemp, Log, TEXT("RankingPlayerStatuses_Num=%d"), RankingPlayerStatuses.Num());
	for (int i = 0; i < RankingPlayerStatuses.Num(); i++) {
		if (PlayerTopStatus.score > RankingPlayerStatuses[i].score) {
			PlayerTopStatus.rank = (i + 1);
			UE_LOG(LogTemp, Log, TEXT("Rank=%d"), PlayerTopStatus.rank);
			UE_LOG(LogTemp, Log, TEXT("Score=%d"), PlayerTopStatus.score);
			IsRankIn = true;
			break;
		}
	}
}

void UTMMAGameInstanceBase::RankIn() {
	for (int i = 0; i < RankingPlayerStatuses.Num(); i++) {
		if (PlayerTopStatus.score > RankingPlayerStatuses[i].score) {
			FRankingPlayerStatus DownRankStatus = RankingPlayerStatuses[i];
			RankingPlayerStatuses[i] = PlayerTopStatus;
			DownRankStatus.rank += 1;
			for (int j = i + 1; j < RankingPlayerStatuses.Num(); j++) {
				FRankingPlayerStatus TraceRankStatus = RankingPlayerStatuses[j];
				RankingPlayerStatuses[j] = DownRankStatus;
				TraceRankStatus.rank += 1;
				DownRankStatus = TraceRankStatus;
			}
			break;
		}
	}
}

void UTMMAGameInstanceBase::SavePlayerStatus()
{
	int CurrentScore = Player1Score;
	if (CurrentScore > PlayerTopStatus.score) {
		PlayerTopStatus.score = CurrentScore;
		PlayerTopStatus.stage = CurrentStage;
	}
	UE_LOG(LogTemp, Log, TEXT("UTMMAGameInstance::SavePlayerStatus() Completed"));
}

// サウンド関連
// BGM再生とオーディオコンポーネント設定.
void UTMMAGameInstanceBase::SpawnAndSetBgm(EGameSoundType InSoundType, int InIndexOfType)
{
	bool IsFinded = false;
	FGameSoundStruct GameSoundStruct = GetGameSoundStruct(InSoundType, InIndexOfType, IsFinded);
	if (!IsFinded) return; // 見つからなければ何もしない
	UE_LOG(LogTemp, Log, TEXT("stage bgm struct get OK."));
	// オーディオコンポーネントの生成と再生
	UAudioComponent* SpawnAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), GameSoundStruct.SoundBaseInstance, 2.0, 1.0, 0.0, nullptr, true);
	if (SpawnAudioComponent == nullptr) return;
	UE_LOG(LogTemp, Log, TEXT("audio component spawn OK."));
	StageBgmComponent = SpawnAudioComponent;
}

// BGMをフェードアウトさせる
void UTMMAGameInstanceBase::FadeOutBgm()
{
	if (StageBgmComponent != nullptr) {
		StageBgmComponent->FadeOut(0.5f, 0.0);
	}
}

// BGMのストップ
void UTMMAGameInstanceBase::StopBgm()
{
	if (StageBgmComponent) {
		StageBgmComponent->Stop();
	}
}

// データアセットからサウンドデータ構造体の設定
void UTMMAGameInstanceBase::SetSoudStructByDataAsset(UTMMASoundManagerDataAsset* InSoundDataAsset)
{
	if (InSoundDataAsset != nullptr) {
		for (FSoftSoundStruct SoftSoundStruct : InSoundDataAsset->SoftSoundStructList) {
			FGameSoundStruct SoundStruct;
			SoundStruct.SoundBaseInstance = SoftSoundStruct.SoftSoundBase.LoadSynchronous();
			if (SoundStruct.SoundBaseInstance == nullptr) {
				// サウンドデータ読み込み失敗でスキップ.
				continue;
			}
			SoundStruct.SoundType = SoftSoundStruct.SoundType;
			SoundStruct.IndexOfType = SoftSoundStruct.IndexOfType;
			SoundStructList.Add(SoundStruct);
			UE_LOG(LogTemp, Log, TEXT("sound asset load and set OK."));
		}
	}
}

// コイン追加
void UTMMAGameInstanceBase::InsertCoin()
{
	// クレジットが最大に達している場合は行わない.
	if (CreditCount >= MAX_CREDIT_COUNT) return;
	CoinCount++;
	UE_LOG(LogTemp, Log, TEXT("coin inserted coins:%d"), CoinCount);
	// 1クレジットに必要なコイン数を満たしていたら、1クレジット追加
	if ((CoinCount % UseCoinByCredit) == 0) {
		AddCredit();
	}
}

// 1クレジットの消費コイン数の設定 ※オプションとかで設定できるようにしておく.
void UTMMAGameInstanceBase::SetUseCoinByCredit(int InUseCoinByCredit)
{
	UseCoinByCredit = InUseCoinByCredit;
}

void UTMMAGameInstanceBase::AddCredit()
{
	if (CreditCount >= MAX_CREDIT_COUNT) return; // クレジット上限に達している.
	CreditCount++;
	UE_LOG(LogTemp, Log, TEXT("credit inserted credits:%d"), CreditCount);
}

void UTMMAGameInstanceBase::UseCredit()
{
	CreditCount--;
	UE_LOG(LogTemp, Log, TEXT("use credit credits:%d"), CreditCount);
	// TODO::いずれ、コンティニューでの使用コイン数は別になった時とか考えておきたい.
	CoinCount -= UseCoinByCredit;
	UE_LOG(LogTemp, Log, TEXT("use coin coins:%d"), CreditCount);
}