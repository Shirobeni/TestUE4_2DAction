// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMASemiBoss4Base.h"

void ATMMASemiBoss4Base::BeginPlay()
{
	Super::BeginPlay();
	PatternCountChangeMod = 30;
	PatternCountEndCount = 300;
}

void ATMMASemiBoss4Base::FunctionByTimerEvent()
{
	Super::FunctionByTimerEvent();
	AddLivingTime(0.1f);
	if (LivingTime <= 55.0f) {
		CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
		BossAction();
	}
	else {
		MoveEnemy(FVector(0.0f, -20.0f, 0.0f));
	}
}

void ATMMASemiBoss4Base::BossAction()
{
	switch (PatternType) 
	{
		default:
			break;
		case 0:
			MoveEnemy(FVector(0.0f, -5.0f, 0.0f));
			break;
		case 1:
			ShotDelayFloat1 = 0.1f;
			ShotDelayFunction(&ShotFloat1, ShotDelayFloat1, [this]() {
				ShotEnemyBullet2Way();
			});
			break;
		case 2:
			ShotEnemyBulletWay();
			break;
		case 4:
			ShotDelayFloat1 = 0.2f;
			ShotDelayFunction(&ShotFloat1, ShotDelayFloat1, [this]() {
				ShotDestroyableBulletWay();
			});
			break;
		case 5:
		case 6:
			ShotDelayFunction(&ShotFloat1, ShotDelayFloat1, [this]() {
				ShotDestroyableBulletWay();
			});
			ShotDelayFunction(&ShotFloat2, ShotDelayFloat2, [this]() {
				ShotMissile();
			});
			break;
		case 7:
			MoveEnemy(FVector(0.0f, 5.0f, 0.0f));
			break;
	}
}

void ATMMASemiBoss4Base::ShotEnemyBullet2Way()
{
	FVector SetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	float CombineAngle = UKismetMathLibrary::RandomFloat() * 15.0f;
	ShotEnemyWayBulletAimByIndex(SetVector, PlayerLocation, ScaleVector, 3, CombineAngle, 0);
}

void ATMMASemiBoss4Base::ShotEnemyBulletWay()
{
	FVector SetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	FVector ScaleVector = FVector(0.3f, 0.3f, 0.3f);
	float CombineAngle = UKismetMathLibrary::RandomFloat() * 5.0f;
	ShotEnemyWayBulletAimByIndex(SetVector, PlayerLocation, ScaleVector, 3, CombineAngle, 1);
}

void ATMMASemiBoss4Base::ShotDestroyableBulletWay()
{
	FVector SetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	FVector ScaleVector = FVector(0.3f, 0.3f, 0.3f);
	float CombineAngle = UKismetMathLibrary::RandomFloat() * 30.0f;
	ShotEnemyWayBulletAimByIndex(SetVector, PlayerLocation, ScaleVector, 3, CombineAngle, 2);
}

void ATMMASemiBoss4Base::ShotMissile()
{
	FVector SetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector TargetVector = FVector(0.0f, 0.0f, 0.0f);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	AActor* SpawnMissile;
	ShotEnemyBulletAimByIndex(SetVector, TargetVector, 3, ScaleVector, SpawnMissile);
}
