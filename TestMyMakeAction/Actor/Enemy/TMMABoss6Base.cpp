
// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss6Base.h"
#include "TestMyMakeAction/AI/TMMABoss6AiBase.h"
#include "AIController.h"


void ATMMABoss6Base::BeginPlay()
{
	Super::BeginPlay();
	PatternCountChangeMod = 0;
	// 専用AIコントローラークラスをキャストして、連携させる.
	if (AAIController* AIController = Cast<AAIController>(Controller)) {
		if (ATMMABoss6AiBase* CastedBoss6AI = Cast<ATMMABoss6AiBase>(AIController)) {
			Boss6AI = CastedBoss6AI;
			PatternTransform = 1;
		}
	}
}

void ATMMABoss6Base::FunctionByTimerEvent()
{
	if ((!GameMode->GetIsBossBattle()) || IsDefeated) return;
	PatternType = Boss6AI->GetDestinationIndex();
	BossAttack();
	if (Hp < 7000 && IsTransformDoOnce == false) {
		IsTransformDoOnce = true;
		PatternTransform = 2;
		UTMMAActorLibrary::SpawnSeAndParticleBySoft(this, TransformParticle, TransformSound, GetActorLocation(), FVector(1.0f, 1.0f, 1.0f));
		DestroyAllSpawnActor();
	}
}

void ATMMABoss6Base::BossAttack()
{
	if (!Boss6AI->GetIsArrivedPoint()) return; 
	UE_LOG(LogTemp, Warning, TEXT("TimerEventFlame=%f"), TimerEventFlame);
	UE_LOG(LogTemp, Warning, TEXT("ShotFloat=%f"), ShotFloat);
	switch (PatternTransform) {
		default:
			break;
		case 1:
			ShotPatternByPt1();
			break;
		case 2:
			ShotPatternByPt2();
			break;
	}
}

void ATMMABoss6Base::ShotPatternByPt1()
{
	switch (PatternType) {
		default:
			break;
		case 0:
			ShotDelayFloat = 1.0f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotRiseBulletWay();
			});
			break;
		case 1:
			ShotDelayFloat = 0.3f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotEnemyBulletWay();
			});
			break;
		case 2:
			ShotDelayFloat = 0.6f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotHomingBullet();
			});
			break;
		case 3:
			ShotDelayFloat = 0.2f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotEnemyDestroyBullet();
			});
			break;
	}
}

void ATMMABoss6Base::ShotPatternByPt2()
{
	switch (PatternType) {
		default:
			break;
		case 0:
			ShotDelayFloat = 0.1f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotDestroyableMissile();
			});
			break;
		case 1:
			ShotDelayFloat = 0.2f;
			ShotWinderWay();
			break;
	}

}

void ATMMABoss6Base::ShotEnemyBulletWay()
{
	FVector SetVector = FVector(0.0f, 0.0f, 0.0f);
	FVector PlayerVector;
	UTMMAActorLibrary::GetPlayerLocation(PlayerVector);
	FVector ScaleVector = FVector(0.5f, 0.3f, 0.3f);
	ShotEnemyWayBulletAimByIndex(SetVector, PlayerVector, ScaleVector, 3, 30.0f, 0);
}

void ATMMABoss6Base::ShotHomingBullet()
{
	FVector StartVector = FVector(0.0f, 0.0f, 0.0f);
	FVector PlayerVector;
	UTMMAActorLibrary::GetPlayerLocation(PlayerVector);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	AActor* HomingBullet;
	ShotEnemyBulletAimByIndex(StartVector, PlayerVector, 1, ScaleVector, HomingBullet);
}

void ATMMABoss6Base::ShotRiseBulletWay()
{
	FVector SetVector = FVector(0.0f, 0.0f, 0.0f);
	FVector ScaleVector = FVector(0.5f, 0.3f, 0.3f);
	ShotEnemyWayBulletAimByIndex(SetVector, GetActorLocation(), ScaleVector, 3, 90.0f, 2);
}

void ATMMABoss6Base::ShotEnemyDestroyBullet()
{
	FVector SetVector = FVector(0.0f, 0.0f, 0.0f);
	FVector PlayerVector;
	UTMMAActorLibrary::GetPlayerLocation(PlayerVector);
	FVector ScaleVector = FVector(0.5f, 0.3f, 0.3f);
	ShotEnemyWayBulletAimByIndex(SetVector, PlayerVector, ScaleVector, 3, 15.0f, 3);
}

void ATMMABoss6Base::ShotDestroyableMissile()
{
	FVector SetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector PlayerVector;
	UTMMAActorLibrary::GetPlayerLocation(PlayerVector);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	ShotEnemyWayBulletAimByIndex(SetVector, PlayerVector, ScaleVector, 3, 120.0f, 4);
}

void ATMMABoss6Base::ShotWinderWay()
{
	FVector SetVector = FVector(1.0f, 1.0f, 1.0f);
	FVector TargetVector = FVector(0.5, 0.5, 0.5);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	ShotEnemyWayBulletAimByIndex(SetVector, TargetVector, ScaleVector, 5, 5.0f, 5);
}

