// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMATitleWidget.h"
#include "GameMode/TMMATitleGameMode.h"

void UTMMATitleWidget::DecideMenu()
{
	int MenuIndex = StartMenu->GetSelectedButtonRowColumn().index;
	switch (MenuIndex) {
		default:
			break;
		case 0:
			// ゲームスタート
			if (ATMMATitleGameMode* TitleGameMode = Cast<ATMMATitleGameMode>(UGameplayStatics::GetGameMode(GetWorld()))) {

				TitleGameMode->StartGame();
			}
	}
}

void UTMMATitleWidget::SetStartMenu(UTMMAItemList* InStartMenu)
{
	StartMenu = InStartMenu;
}

void UTMMATitleWidget::StartGame(int InItemIndex, APlayerController* InPlayerController)
{
	// TODO::実際に実装が必要か検討中.
//	if (InItemIndex == 0) {
//		InPlayerController->SetInputMode(FInputModeGameOnly());
//		UGameplayStatics::OpenLevel(GetWorld(), )
//	}
}

void UTMMATitleWidget::InitViewCountAndComma()
{
	ViewCount = 5;
	ViewComma = 10.0f;
}

void UTMMATitleWidget::ReduceViewCount()
{
	if (IsLockViewCount == false) {
		if (ViewCount >= 0) {
			ViewComma -= 0.1f;
			if (ViewComma < 0.0f) {
				ViewCount -= 1;
				ViewComma = 10.0f;
			}
		}
		else {
			IsView = false;
		}
	}
}

void UTMMATitleWidget::SetIsLockViewCount(bool InIsLockViewCount)
{
	IsLockViewCount = InIsLockViewCount;
}

void UTMMATitleWidget::SetIsView(bool InIsView)
{
	IsView = InIsView;
}

void UTMMATitleWidget::ChangeViewCanvas(EViewMode InViewMode)
{
	ViewMode = InViewMode;
	switch (ViewMode) {
		case EViewMode::Title:
			IsView = true;
			RankingWidget->InitViewCountAndComma();
			TitleCanvas->SetVisibility(ESlateVisibility::Visible);
			RankingCanvas->SetVisibility(ESlateVisibility::Hidden);
			break;
		case EViewMode::Ranking:
			IsView = false;
			InitViewCountAndComma();
			TitleCanvas->SetVisibility(ESlateVisibility::Hidden);
			RankingCanvas->SetVisibility(ESlateVisibility::Visible);
			break;
		default:
			break;
	}
}
