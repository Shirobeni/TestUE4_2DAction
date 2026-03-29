// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss7AiBase.h"

void ATMMABoss7AiBase::BeginPlay()
{
	Super::BeginPlay();
	if (ATMMABoss7Base* CastedBoss7 = Cast<ATMMABoss7Base>(GetPawn())) {
		Boss7 = CastedBoss7;
	}
}

void ATMMABoss7AiBase::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (!Boss7) return;
	UE_LOG(LogTemp, Log, TEXT("Boss7 PatternTransform : %d"), Boss7->GetPatternTransform()); //　形態数を取得.(※確認のため)
	if (Result.IsSuccess())
	{
		if (Boss7->GetPatternTransform() == 2 || Boss7->GetPatternTransform() == 3) {
			Boss7->SetIsWait(false);
			if (Boss7->GetPatternTransform() == 3) {
//				Boss7->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
				Boss7->GetCharacterMovement()->GravityScale = 0.0f;
			}
		}
	}
}
