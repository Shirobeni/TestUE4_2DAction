// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMARankingRowWidgetBase.h"

void UTMMARankingRowWidgetBase::SetRankingParamAndText(int InRank, FString InName, int InScore, int InStage) 
{
	RankingParam.rank = InRank;
	RankingParam.name = InName;
	RankingParam.score = InScore;
	RankingParam.stage = InStage;
	if (RankText != nullptr) {
		FString RankChar = "";
		switch (InRank)
		{
		case 1:
			RankChar = "1st";
			break;
		case 2:
			RankChar = "2nd";
			break;
		case 3:
			RankChar = "3rd";
			break;
		default:
			if (InRank >= 4 && InRank <= 10) {
				RankChar = FString::Printf(TEXT("%dth"), RankingParam.rank);
			}
			break;
		}
		RankText->SetText(FText::FromString(RankChar));
	}
	if (NameText != nullptr) {
		NameText->SetText(FText::FromString(RankingParam.name));
	}
	if (ScoreText != nullptr) {
		ScoreText->SetText(FText::FromString(FString::FromInt(RankingParam.score)));
	}
	if (StageText != nullptr) {
		FString StageChar = "";
		switch (InStage)
		{
		case 0:
			StageChar = "ALL";
			break;
		default:
			StageChar = FString::Printf(TEXT("AR.%d"), RankingParam.stage);
			break;
		}
		StageText->SetText(FText::FromString(StageChar));
	}
}

void UTMMARankingRowWidgetBase::SetRankingParamAndTextFromStatus(FRankingPlayerStatus RankingPlayerStatus)
{
	int Rank = RankingPlayerStatus.rank;
	FString Name = RankingPlayerStatus.player_name;
	int Score = RankingPlayerStatus.score;
	int Stage = RankingPlayerStatus.stage;
	SetRankingParamAndText(Rank, Name, Score, Stage);
}

