// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMARankingWidgetBase.h"

void UTMMARankingWidgetBase::InitViewCountAndComma()
{
	ViewCount = 5;
	ViewComma = 10.0f;
}

void UTMMARankingWidgetBase::ReduceViewCount()
{
	if (ViewCount >= 0) {
		ViewComma -= 0.1f;
		if (ViewComma < 0.0f) {
			ViewCount -= 1;
			ViewComma = 10.0f;
		}
	}
	else {
		SetIsView(false);
	}
}

void UTMMARankingWidgetBase::SetRankingData(TArray<FRankingPlayerStatus> RankingPlayerStatuses)
{
	if (RankingRowWidget != nullptr) {
		for (int i = 0; i < RankingPlayerStatuses.Num(); i++) {
			if (RankingPlayerStatuses.IsValidIndex(i)) {
				UTMMARankingRowWidgetBase* PlayerRankingRow = CreateWidget<UTMMARankingRowWidgetBase>(GetWorld(), RankingRowWidget);
				RankingVerticalBox->AddChildToVerticalBox(PlayerRankingRow);
				PlayerRankingRow->SetRankingParamAndTextFromStatus(RankingPlayerStatuses[i]);
			}
		}
	}
}

void UTMMARankingWidgetBase::SetIsView(bool InIsView)
{
	IsView = InIsView;
}
