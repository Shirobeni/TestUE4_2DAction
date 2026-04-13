// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAPlayerState.h"
#include "TestMyMakeAction/TMMAGameInstanceBase.h"
#include "TestMyMakeAction/Controller/TMMAPlayerController.h"

void ATMMAPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ATMMAPlayerState::TakeOverPlayerStatusToStage(UTMMAGameInstanceBase* InGameInstance)
{
	if (!InGameInstance) return;
	Score = InGameInstance->Get1PScore();
	Left = InGameInstance->GetP1Left();
	NextExtendScore = InGameInstance->GetP1NextExtendScore();
	UE_LOG(LogTemp, Log, TEXT("P1NextExtendScore:%d"), InGameInstance->GetP1NextExtendScore());
	ExtendCount = InGameInstance->P1ExtendCount;
}

void ATMMAPlayerState::SetPlayerStateByContinue(UTMMAGameInstanceBase* InGameInstance)
{
	Score = InGameInstance->Get1PScore();
	Left = InGameInstance->GetP1Left();
	ExtendCount = 0;
	NextExtendScore = DEFAULT_FIRST_EXTEND_SCORE;
}

void ATMMAPlayerState::SetControllerByCast()
{
	if (ATMMAPlayerController* CastedPlayerController = Cast<ATMMAPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		MainPlayerController = CastedPlayerController;
	}
}

void ATMMAPlayerState::SetScore(int InScore)
{
	Score = InScore;
}

void ATMMAPlayerState::AddScore(int InAddedScore)
{
	Score += InAddedScore;
}

void ATMMAPlayerState::SetLeft(int InLeft) 
{
	Left = InLeft;
}

void ATMMAPlayerState::ChangeLeft(bool IsExtend)
{
	// エクステンドなら1機増やす
	if (IsExtend) {
		Left++;
	}
	else {
		// そうでなければ1機減らす
		Left--;
	}
}

void ATMMAPlayerState::CheckExtendPlayer(bool& IsExtend)
{
	bool ExtendFlag = false;
	if (Score >= NextExtendScore) {
		UE_LOG(LogTemp, Log, TEXT("NowExtend...=%d"), NextExtendScore);
		UE_LOG(LogTemp, Log, TEXT("Player1Score to ExtendTiming...=%d"), Score);
		Left++;
		ExtendCount++;
		NextExtendScore = ExtendCount * DEFAULT_EVERY_EXTEND_SCORE;
		UE_LOG(LogTemp, Log, TEXT("NextExtend...=%d"), NextExtendScore);
		ExtendFlag = true;
		if (!MainPlayerController->GetMainGameWidget()) return;
		MainPlayerController->GetMainGameWidget()->UpdateLeft(Left);
	}
	IsExtend = ExtendFlag;
}
