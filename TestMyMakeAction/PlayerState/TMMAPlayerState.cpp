// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAPlayerState.h"

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

