// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMASemiBoss3Base.h"

void ATMMASemiBoss3Base::BeginPlay()
{
	Super::BeginPlay();
	PatternCountChangeMod = 120;
	PatternCountEndCount = 120;
}

void ATMMASemiBoss3Base::FunctionByTimerEvent()
{
	Super::FunctionByTimerEvent();
	if (!WasRecentlyRendered(0.0f)) return;
	if (!GameMode->GetIsBossBattle() || IsDefeated) return;
	CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
	ShotDelayFunction(&ShotFloat1, ShotDelayFloat1, [this]() {
		ShotEnemyBulletByCircle();
	});
	if (Hp > 2000) {
		ShotDelayFloat2 = 0.1f;
		ShotDelayFunction(&ShotFloat2, ShotDelayFloat2, [this]() {
			ShotDestroyableBullet();
		});
	}
	else {
		UTMMAActorLibrary::MoveActorToTarget(this, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), 0.2f);
		ShotDelayFloat2 = 0.4f;
		ShotDelayFunction(&ShotFloat2, ShotDelayFloat2, [this]() {
			ShotMissile();
		});
	}
}

void ATMMASemiBoss3Base::ShotEnemyBulletByCircle()
{
	FVector SetVector = FVector(0.0f, 0.0f, 0.0f);
	FVector InVector = FVector(0.0f, 1.0f, 0.0f);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	float AddingRotateRollParam = (PatternCount / 10) * 30.0f;
	FRotator AddRotator = FRotator(AddingRotateRollParam, 0.0f, 0.0f);
	AActor* SpawnShot;
	ShotEnemyBulletXVectorByCombineByIndex(SetVector, InVector, 0, ScaleVector, AddRotator, SpawnShot);
}

void ATMMASemiBoss3Base::ShotDestroyableBullet()
{
	FVector SetVector = FVector(0.0f, 0.0f, 0.0f);
	FVector InVector = FVector(0.0f, 1.0f, 0.0f);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	float AddingRotateRollParam = UKismetMathLibrary::RandomFloat() * 90.0f;
	FRotator AddRotator = FRotator(AddingRotateRollParam, 0.0f, AddingRotateRollParam);
	AActor* SpawnShot;
	ShotEnemyBulletXVectorByCombineByIndex(SetVector, InVector, 1, ScaleVector, AddRotator, SpawnShot);
}

void ATMMASemiBoss3Base::ShotMissile()
{
	FVector SetVector = FVector(0.0f, 0.0f, 0.0f);
	FVector InVector = FVector(0.0f, 0.0f, 0.0f);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	AActor* SpawnShot;
	ShotEnemyBulletAimByIndex(SetVector, InVector, 2, ScaleVector, SpawnShot);
}