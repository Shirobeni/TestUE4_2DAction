// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss6AiBase.h"

void ATMMABoss6AiBase::BeginPlay()
{
	Super::BeginPlay();
	if (ATestMyMakeActionGameModeBase* CastedMainGameMode = Cast<ATestMyMakeActionGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))) {
		MainGameMode = CastedMainGameMode;
	}
	if (ATMMABoss6Base* CastedBoss6 = Cast<ATMMABoss6Base>(GetPawn())) {
		Boss6 = CastedBoss6;
		DestinationPointActorListPt1 = Boss6->DestinationPointActorListPt1;
		DestinationPointActorListPt2 = Boss6->DestinationPointActorListPt2;
		SetDestinationVector();
		DelicadeTime = 10.0f;
//		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss6AiBase::MovePatroll, DelicadeTime, true);
	}
}

void ATMMABoss6AiBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!MainGameMode->GetIsBossBattle()) return;
	if (Boss6->GetEnemyHp() <= 7000 && IsTransformDoOnceFlag == false) {
		IsArrivedPoint = false; // 第一形態の攻撃を中断させ、移動状態にする.
		DelicadeTime = 20.0f;
		DestinationIndex = 0;
		IsTransformDoOnceFlag = true;
	}
	MovePatroll();
	AddAttackintTime();
}

void ATMMABoss6AiBase::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (Result.IsSuccess())
	{
		IsArrivedPoint = true;
	}
}

void ATMMABoss6AiBase::PopDestinationLocation()
{
	if (!Boss6) return;
	if (DestinationPointActorListPt1.Num() <= 0) return;
	if (DestinationPointActorListPt2.Num() <= 0) return;
	switch (Boss6->GetPatternTransform()) {
		case 2:
			DestinationIndex = ((DestinationIndex + 1) % DestinationPointActorListPt2.Num());
			break;
		default:
			DestinationIndex = ((DestinationIndex + 1) % DestinationPointActorListPt1.Num());
			break;
	}
}

void ATMMABoss6AiBase::MovePatroll()
{
	if (IsArrivedPoint) return;
	AccelerationValue += 0.2f;
	UTMMAActorLibrary::MoveActorToTarget(Boss6, TargetDestinationPointActor, (10.0f + AccelerationValue));
	if (FVector::Dist(Boss6->GetActorLocation(), TargetDestinationPointActor->GetActorLocation()) < 10.0f) {
		Boss6->SetActorLocation(TargetDestinationPointActor->GetActorLocation());
		PopDestinationLocation();
		SetDestinationVector();
		IsArrivedPoint = true;
		AccelerationValue = 0.0f;
	}
//	EPathFollowingRequestResult::Type MovePathModeResult = MoveToLocation(DestinationVector);
}

void ATMMABoss6AiBase::AddAttackintTime()
{
	if (!IsArrivedPoint) return;
	AttackingTime += 0.1f; // 攻撃時間の加算
	// 攻撃時間がデリケードタイム以上になったら、移動モードにして中断.
	if (AttackingTime >= DelicadeTime) {
		IsArrivedPoint = false;
		AttackingTime = 0.0f;
	}
}

void ATMMABoss6AiBase::SetDestinationVector()
{
	if ((!Boss6) || (DestinationPointActorListPt1.Num() <= 0) || (DestinationPointActorListPt2.Num() <= 0)) return;
	switch (Boss6->GetPatternTransform()) {
		case 2:
			DestinationVector = DestinationPointActorListPt2[DestinationIndex]->GetActorLocation();
			TargetDestinationPointActor = DestinationPointActorListPt2[DestinationIndex];
			break;
		default:
			DestinationVector = DestinationPointActorListPt1[DestinationIndex]->GetActorLocation();
			TargetDestinationPointActor = DestinationPointActorListPt1[DestinationIndex];
			break;
	}
}

// 形態変更後にDelayで実行するため
void ATMMABoss6AiBase::InitDestinationIndexForDelay()
{
	DestinationIndex = 0;
}
