// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAMaingameWidgetBase.h"
#include "TestMyMakeActionGameModeBase.h"

void UTMMAMaingameWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	// あらかじめゲームステートを設定しておく
	if (ATMMAGameStateBase* CastedMainGameState = Cast<ATMMAGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))) {
		MainGameState = CastedMainGameState;
	}

	Player1ScoreText->TextDelegate.BindUFunction(this, "SetPlayer1ScoreText");
	TimeText->TextDelegate.BindUFunction(this, "SetTimeText");
	HighScoreText->TextDelegate.BindUFunction(this, "SetHighScoreText");

}


bool UTMMAMaingameWidgetBase::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	Player1ScoreText->TextDelegate.BindUFunction(this, "SetPlayer1ScoreText");
	TimeText->TextDelegate.BindUFunction(this, "SetTimeText");
	HighScoreText->TextDelegate.BindUFunction(this, "SetHighScoreText");

	return true;
}


void UTMMAMaingameWidgetBase::SetLeftIcon(TSubclassOf<UTMMAPlayerLeftWidgetBase> InPlayerLeftIcon)
{
	PlayerLeftIcon = InPlayerLeftIcon;
}

void UTMMAMaingameWidgetBase::UpdateLeft(int InViewCount)
{
	if ((PlayerLeftIcon != nullptr) && (LeftIconList != nullptr))
	{
		LeftIconList->ClearChildren();
		for (int i = 0; i < InViewCount; i++) {
			UTMMAPlayerLeftWidgetBase* PlayerLeftIconClass = CreateWidget<UTMMAPlayerLeftWidgetBase>(GetWorld(), PlayerLeftIcon);
			LeftIconList->AddChild(PlayerLeftIconClass);
		}
	}
}

void UTMMAMaingameWidgetBase::UpdateBurstCount(int InBurstCount)
{
	if (P1BurstCountText != nullptr)
	{
		P1BurstCountText->SetText(FText::FromString(FString::FromInt(InBurstCount)));
	}
}

void UTMMAMaingameWidgetBase::SetStageAndStageTitleText(int CurrentStageNum, EBuildMode InBuildMode)
{
	FString StageName = FString::Printf(TEXT("AREA%d"),CurrentStageNum);
	FString StageSubTitle = "";
	// ビルド状態によって行う.
	switch (InBuildMode) {
		default:
			break;
		case EBuildMode::Release:
		case EBuildMode::Development:
			switch (CurrentStageNum) {
				case 1:
					StageSubTitle = "RUNAWAY";
					break;
				case 2:
					StageSubTitle = "BREAKING THE LAW";
					break;
				case 3:
					StageSubTitle = "ARE YOU GONNA GO MY WAY";
					break;
				case 4:
					StageSubTitle = "I WANT OUT";
					break;
				case 5:
					StageSubTitle = "ROCKET RIDE";
					break;
				case 6:
					StageSubTitle = "BAD MEDICINE";
					break;
				case 7:
					StageSubTitle = "KILLING IN THE NAME";
					break;
				default:
					break;
			}
			break;
		case EBuildMode::SNS:
			switch (CurrentStageNum) {
			case 1:
				StageSubTitle = "RUNAWAY AND ASSAULT";
				break;
			case 2:
				StageSubTitle = "REVELOIN TO FREE";
				break;
			case 3:
				StageSubTitle = "RAILLOAD OF RAID";
				break;
			case 4:
				StageSubTitle = "BROKEN PURE HEARTS";
				break;
			case 5:
				StageSubTitle = "RIDE TO DEATHWIND";
				break;
			case 6:
				StageSubTitle = "WEALTN OF MADNESS MEDICINE";
				break;
			case 7:
				StageSubTitle = "RUIN OF AUTHORITIES";
				break;
			default:
				break;
			}
			break;
	}
	
	if (StageText != nullptr) {
		StageText->SetText(FText::FromString(StageName));
	}
	if (StageSubTitleText != nullptr) {
		StageSubTitleText->SetText(FText::FromString(StageSubTitle));
	}
}

void UTMMAMaingameWidgetBase::AddStageTitleViewTime()
{
	if (StageTitleViewTimeStopFlag == false) {
		StageTitleViewTime += 0.1f;
		if (StageTitleViewTime >= MaxStageTitleViewTime) {
			StageTitleViewTimeStopFlag = true;
			StageTitleViewTime = 0.0f;
			if (StageTitlePanel != nullptr) {
				StageTitlePanel->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UTMMAMaingameWidgetBase::SetDirectionWidgetByIsLeftSide(bool InIsDirectionLeftSide)
{
	FVector2D Translation = FVector2D(1140.0f, 140.0f);
	if (InIsDirectionLeftSide == true) {
		Translation = (FVector2D(200.0f, 128.0f));
	}
	UCanvasPanelSlot* DirectionWidgetCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(DirectionWidget);
	if (DirectionWidgetCanvasSlot != nullptr) {
		DirectionWidgetCanvasSlot->SetPosition(Translation);
	}

}

FText UTMMAMaingameWidgetBase::SetPlayer1ScoreText()
{
	int Score = 0;
	if (MainGameState != nullptr) {
		if (MainGameState->GetP1PlayerState() != nullptr) {
			Score = MainGameState->GetP1PlayerState()->GetScore();
		}
	}
	return (FText::FromString(FString::FromInt((int)Score)));
}

FText UTMMAMaingameWidgetBase::SetTimeText()
{
	if (MainGameState != nullptr) {
		return (FText::FromString(FString::FromInt((int)MainGameState->GetLeftStageTimeByConvertInt())));
	}
	return FText();
}

FText UTMMAMaingameWidgetBase::SetHighScoreText()
{
	if (MainGameState != nullptr) {
		return (FText::FromString(FString::FromInt((int)MainGameState->GetHighScore())));
	}
	return FText();
}