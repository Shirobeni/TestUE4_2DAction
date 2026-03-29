// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMANameRegistWidget.h"

void UTMMANameRegistWidget::InitNameRegistCountAndComma()
{
	NameRegistComma = 10.0f;
	NameRegistCount = 20;
}

void UTMMANameRegistWidget::ReduceNameRegistTime()
{
	if (NameRegistCount >= 0) {
		NameRegistComma -= 0.1f;
		UE_LOG(LogTemp, Log, TEXT("NameRegistComma=%f"), NameRegistComma);
		UE_LOG(LogTemp, Log, TEXT("NameRegistCount=%d"), NameRegistCount);
		if (NameRegistComma <= 0.0f) {
			NameRegistCount -= 1;
			NameRegistComma = 10.0f;
		}
	}
	else {
		SetIsCompleteRegist(true);
	}
}

void UTMMANameRegistWidget::SetIsCompleteRegist(bool InIsCompleteRegist)
{
	IsCompleteRegist = InIsCompleteRegist;
}

void UTMMANameRegistWidget::SetScoreAndRankText(int InRank, int InScore)
{
	FString RankChar = "";
	if (RankText != nullptr) {
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
					RankChar = FString::Printf(TEXT("%dth"), InRank);
				}
				break;
		}
		RankText->SetText(FText::FromString(RankChar));
	}
	if (ScoreText != nullptr) {
		ScoreText->SetText(FText::FromString(FString::FromInt(InScore)));
	}
}

void UTMMANameRegistWidget::SetStageText(int InStage)
{
	FString StageChar = "";
	if (StageText != nullptr) {
		switch (InStage)
		{
			case 0:
				StageChar = "ALL";
				break;
			default:
				StageChar = FString::Printf(TEXT("AR.%d"), InStage);
				break;
		}
		StageText->SetText(FText::FromString(StageChar));
	}
}


void UTMMANameRegistWidget::InitRegistCharacters()
{
	FString RegistName = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-!?";
	UE_LOG(LogTemp, Log, TEXT("RegistNameLength=%d"), RegistName.Len());
	for (int i = 0; i < RegistName.Len(); i++) {
		FRegistCharacter InsertRegistCharacter;
		InsertRegistCharacter.character = RegistName.Mid(i, 1);
		InsertRegistCharacter.index = i;
		RegistCharacters.Add(InsertRegistCharacter);
	}
}

void UTMMANameRegistWidget::SetSelectRegistCharacter(int InIndex) 
{
	SelectRegistCharacter.index = RegistCharacters[InIndex].index;
	SelectRegistCharacter.character = RegistCharacters[InIndex].character;
}

void UTMMANameRegistWidget::MoveAndGetRegistCharacter(int AddIndex, FString& ReturnCharacter)
{
	int NextIndex = SelectRegistCharacter.index + AddIndex;
	if (NextIndex >= RegistCharacters.Num()) {
		NextIndex = 0;
	}
	else if (NextIndex < 0) {
		NextIndex = (RegistCharacters.Num() - 1);
	}
	SetSelectRegistCharacter(NextIndex);
	ReturnCharacter = SelectRegistCharacter.character;
}

void UTMMANameRegistWidget::MoveAndGetRegistCharacterByTextBlock(int AddIndex, UTextBlock* InTextBlock, FString& ReturnCharacter)
{
	if (InTextBlock != nullptr) {
		MoveAndGetRegistCharacter(AddIndex, ReturnCharacter);
		InTextBlock->SetText(FText::FromString(ReturnCharacter));
	}
}

void UTMMANameRegistWidget::CreatePlayerName(FString& PlayerName)
{
	FString FirstCharacter = FirstText->GetText().ToString();
	FString SecondCharacter = SecondText->GetText().ToString();
	FString FAndSCharacter = FirstCharacter.Append(SecondCharacter);
	FString ThirdCharacter = ThirdText->GetText().ToString();
	FString AllCharacter = FAndSCharacter.Append(ThirdCharacter);
	PlayerName = AllCharacter;

}

void UTMMANameRegistWidget::AddSelectNameTextNo(int AddNo)
{
	SelectNameTextNo += AddNo;
}