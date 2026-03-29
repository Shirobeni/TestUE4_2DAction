// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss5Base.h"

void ATMMABoss5Base::BeginPlay()
{
	Super::BeginPlay();
	PatternCountChangeMod = 100;
	PatternCountEndCount = 400;
}

void ATMMABoss5Base::FunctionByTimerEvent()
{
	Super::FunctionByTimerEvent();
	if (IsDefeated) return;
	CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
	BossAttack();
	if (IsMoveUp) {
		MoveEnemy(FVector(0.0f, 0.0f, 10.0f));
		if(GetActorLocation().Z > 150.0f) {
			IsMoveUp = false;
		}
	} else {
		MoveEnemy(FVector(0.0f, 0.0f, -10.0f));
		if(GetActorLocation().Z < -150.0f) {
			IsMoveUp = true;
		}
	}
}

void ATMMABoss5Base::BossAttack()
{
	switch (PatternType) {
		default:
			break;
		case 1:
			ShotDelayFloat = 0.2f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotMissile();
			});
//			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss5Base::ShotMissile, 0.2f, false);
			break;
		case 2:
			ShotDelayFloat = 0.2f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotReverseMissile();
			});
//			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss5Base::ShotReverseMissile, 0.2f, false);
			break;
		case 3:
			ShotDelayFloat = 0.2f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotDestroyableBullet();
			});
//			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss5Base::ShotDestroyableBullet, 0.2f, false);
			break;
		case 4:
			ShotDelayFloat = 0.3f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotDestroyableBullet();
			});
//			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss5Base::ShotEnemyWayBullet, 0.3f, false);
			break;
	}
}

void ATMMABoss5Base::ShotMissile()
{
	FVector PlayerVector;
	UTMMAActorLibrary::GetPlayerLocation(PlayerVector);
	FVector SetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector ScaleVector = FVector(0.5f, 0.5f, 0.5f);
	AActor* SpawnMissile;
	ShotEnemyBulletAimByIndex(SetVector, PlayerVector, 0, ScaleVector, SpawnMissile);
}

void ATMMABoss5Base::ShotReverseMissile()
{
	FVector PlayerVector;
	UTMMAActorLibrary::GetPlayerLocation(PlayerVector);
	FVector SetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector ScaleVector = FVector(0.5f, 0.5f, 0.5f);
	AActor* SpawnMissile;
	ShotEnemyBulletAimByIndex(SetVector, PlayerVector, 1, ScaleVector, SpawnMissile);
}

void ATMMABoss5Base::ShotDestroyableBullet()
{
	FVector PlayerVector;
	UTMMAActorLibrary::GetPlayerLocation(PlayerVector);
	FVector SetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector ScaleVector = FVector(0.5f, 0.5f, 0.5f);
	ShotEnemyWayBulletAimByIndex(SetVector, PlayerVector, ScaleVector, 2, 15.0f, 2);
}

void ATMMABoss5Base::ShotEnemyWayBullet()
{
	FVector TargetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector SetVector = FVector(0.0f, 0.0f, 0.0f);
	FVector ScaleVector = FVector(0.3f, 0.3f, 0.3f);
	ShotEnemyWayBulletAimByIndex(SetVector, TargetVector, ScaleVector, 3, 30.0f, 3);
}