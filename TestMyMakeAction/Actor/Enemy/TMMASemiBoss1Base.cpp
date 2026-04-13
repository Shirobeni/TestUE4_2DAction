// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMASemiBoss1Base.h"

void ATMMASemiBoss1Base::BeginPlay()
{
	Super::BeginPlay();
	// ƒ‰ƒ“ƒN‚É‰ž‚¶‚ÄƒVƒ‡ƒbƒgŠÔŠu‚ð’Z‚­‚·‚é
	if (!MainGameState) return;
	ShotAbleCount -= (int)((MainGameState->GetGameRank() / 2));
	MissileDelayFloat -= (float)(MainGameState->GetGameRank() / 2);
}

void ATMMASemiBoss1Base::FunctionByTimerEvent()
{
	if (!WasRecentlyRendered(0.0f)) return;
	if (!GameMode->GetIsBossBattle() || IsDefeated) return;
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		UTMMAActorLibrary::MoveActorToTarget(this, PlayerPawn, 0.3f);
	}
	ShotCount++;
	if (ShotCount >= ShotAbleCount) {
		ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
			ShotEnemyBullet();
		});
	}
	if (ShotCount >= MaxShotCount) {
		ShotCount = 0;
	}
	ShotDelayFunction(&MissileFloat, MissileDelayFloat, [this]() {
		ShotEnemyMissile();
	});
}

void ATMMASemiBoss1Base::ShotEnemyBullet()
{
	FVector StartVector = FVector(1.0f, 1.0f, 1.0f);
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	FVector ScaleVector = FVector(0.3f, 0.3f, 0.3f);
	AActor* SpawnShot;
	ShotEnemyBulletAimByIndex(StartVector, PlayerLocation, 0, ScaleVector, SpawnShot);
}

void ATMMASemiBoss1Base::ShotEnemyMissile()
{
	FVector StartVector = FVector(1.0f, 1.0f, 1.0f);
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	FVector ScaleVector = FVector(0.3f, 0.3f, 0.3f);
	AActor* SpawnShot;
	ShotEnemyBulletAimByIndex(StartVector, PlayerLocation, 1, ScaleVector, SpawnShot);
}