// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss1Base.h"

void ATMMABoss1Base::BeginPlay()
{
	Super::BeginPlay();
	PatternCountChangeMod = 80;
	PatternCountEndCount = 400;
}

void ATMMABoss1Base::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ATMMABoss1Base::FunctionByTimerEvent()
{
	if ((!GameMode->GetIsBossBattle()) || IsDefeated) return;
	CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
	BossAction();
	UE_LOG(LogTemp, Log, TEXT("Pattern Count : %d"), PatternCount);
	UE_LOG(LogTemp, Log, TEXT("Shot Float : %f"), ShotFloat);
}

void ATMMABoss1Base::BossAction()
{
	switch (PatternType) {
		case 0:
			ShotDelayFloat = 0.1f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotPattern1();
			});
			break;
		case 1:
			ShotDelayFloat = 0.6f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotPattern2();
			});
			break;
		case 2:
			ShotDelayFloat = 0.6f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotPattern3();
			});
			break;
		case 3:
			ShotDelayFloat = 0.2f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				ShotPattern4();
			});
			break;
		case 4:
			if (PatternCount >= 360) {
				MoveEnemy(FVector(0.0f, 5.0f, 0.0));
			}
			else {
				MoveEnemy(FVector(0.0f, -5.0f, 0.0));
			}
			break;
		default:
			break;
	}
}

void ATMMABoss1Base::ShotPattern1()
{
	InVector = FVector(0.0f, -1.0f, 0.0f);
	AActor* SpawnShot;
	ShotEnemyBulletXVectorByIndex(FVector(0.0f, 0.0f, 0.0f), InVector, 0, FVector(0.3f, 0.3f, 0.3f), SpawnShot);
}

void ATMMABoss1Base::ShotPattern2()
{
	InVector = FVector(0.0f, -1.0f, 0.0f);
	FVector ActorLocation;
	UTMMAActorLibrary::GetActorLocationForAdd(this, FVector(0.0f, -150.0f, 0.0f), ActorLocation);
	// Transformの生成
	FTransform Transform;
	UTMMAActorLibrary::GetAimTransformForVector(FVector(0.0f, 0.0f, 0.0f), ActorLocation, InVector, FVector(1.0f, 1.0f, 1.0f), Transform);
	AActor* SpawnShot = GetWorld()->SpawnActor<AActor>(ShotEnemyBulletList[1], Transform);
	if (IsValid(SpawnShot)) {
		SpawnShot->AddActorLocalRotation(FRotator(90.0f, 0.0f, 90.0f));
	}
}

void ATMMABoss1Base::ShotPattern3()
{
	// 発射一致設定
	InVector = FVector(0.0f, -1.0f, 1.0f);
	for (int i = -1; i <= 1; i++) {
		// 3方向に弾を発射
		AActor* SpawnShot;
		FRotator AddRotate = FRotator(0.0f, (i * 15.0f), (i * 15.0f));
		ShotEnemyBulletXVectorByCombineByIndex(FVector(0.0f, 0.0f, 0.0f), InVector, 2, FVector(1.0f, 1.0f, 1.0f), AddRotate, SpawnShot);
	}
}

void ATMMABoss1Base::ShotPattern4()
{
	// 自機狙いに設定.
	UTMMAActorLibrary::GetPlayerLocation(InVector);
	FVector ActorLocation;
	UTMMAActorLibrary::GetActorLocationForAdd(this, FVector(0.0f, -150.0f, 0.0f), ActorLocation);
	// Transformの生成
	FTransform Transform;
	UTMMAActorLibrary::GetAimTransformForVector(FVector(0.0f, 0.0f, 0.0f), ActorLocation, InVector, FVector(0.3f, 0.3f, 0.3f), Transform);
	AActor* SpawnShot = GetWorld()->SpawnActor<AActor>(ShotEnemyBulletList[0], Transform);
	if (SpawnShot) {
		// 生成後でないとサイズ指定できないみたいなので、再度指定.
		SpawnShot->SetActorScale3D(FVector(0.3f, 0.3f, 0.3f));
	}
}



