// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAAtructDemoWidgetBase.h"

UTMMAAtructDemoWidgetBase::UTMMAAtructDemoWidgetBase()
{
}

bool UTMMAAtructDemoWidgetBase::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	CoinCountText->TextDelegate.BindUFunction(this, "SetCoinCountText");
	CreditCountText->TextDelegate.BindUFunction(this, "SetCreditCountText");
	return true;
}

void UTMMAAtructDemoWidgetBase::NativeConstruct()
{
	if (UTMMAGameInstanceBase* CastedGameInstance = Cast<UTMMAGameInstanceBase>(GetGameInstance())) {
		GameInstanceBase = CastedGameInstance;
		UE_LOG(LogTemp, Log, TEXT("GameInstance Cast Completed."));
	}
}

void UTMMAAtructDemoWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UTMMAAtructDemoWidgetBase::ChangeWidgetCanvasMode(ELevelMode InLevelMode)
{
	switch (InLevelMode) {
		default:
			// 初期はとりあえずタイトルウィジェット
			TitleCanvas->SetVisibility(ESlateVisibility::Visible);
			DemoPlayCanvas->SetVisibility(ESlateVisibility::Hidden);
			RankingCanvas->SetVisibility(ESlateVisibility::Hidden);
			ReadyStartCanvas->SetVisibility(ESlateVisibility::Hidden);
			break;
		case ELevelMode::DemoPlay:
			TitleCanvas->SetVisibility(ESlateVisibility::Hidden);
			DemoPlayCanvas->SetVisibility(ESlateVisibility::Visible);
			RankingCanvas->SetVisibility(ESlateVisibility::Hidden);
			ReadyStartCanvas->SetVisibility(ESlateVisibility::Hidden);
			break;
		case ELevelMode::Ranking:
			TitleCanvas->SetVisibility(ESlateVisibility::Hidden);
			DemoPlayCanvas->SetVisibility(ESlateVisibility::Hidden);
			RankingCanvas->SetVisibility(ESlateVisibility::Visible);
			ReadyStartCanvas->SetVisibility(ESlateVisibility::Hidden);
			break;
		case ELevelMode::ReadyStart:
			TitleCanvas->SetVisibility(ESlateVisibility::Hidden);
			DemoPlayCanvas->SetVisibility(ESlateVisibility::Hidden);
			RankingCanvas->SetVisibility(ESlateVisibility::Hidden);
			ReadyStartCanvas->SetVisibility(ESlateVisibility::Visible);
			break;
	}
}

// コイン数表示設定
FText UTMMAAtructDemoWidgetBase::SetCoinCountText()
{
	int CoinCount = 0;
	if (GameInstanceBase) {
		UE_LOG(LogTemp, Log, TEXT("CoinCount By GameInstance:%d"), GameInstanceBase->GetCoinCount());
		CoinCount = GameInstanceBase->GetCoinCount();
	}
	return (FText::FromString(FString::FromInt((int)CoinCount)));

}

// クレジット数表示設定
FText UTMMAAtructDemoWidgetBase::SetCreditCountText()
{
	int CreditCount = 0;
	if (GameInstanceBase) {
		UE_LOG(LogTemp, Log, TEXT("CreditCount By GameInstance:%d"), GameInstanceBase->GetCreditCount());
		CreditCount = GameInstanceBase->GetCreditCount();
	}
	return (FText::FromString(FString::FromInt((int)CreditCount)));
}