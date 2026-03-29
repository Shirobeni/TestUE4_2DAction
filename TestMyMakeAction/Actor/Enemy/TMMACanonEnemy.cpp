// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMACanonEnemy.h"

void ATMMACanonEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (UTMMACanonDataAsset* CastedCanonDataAsset = Cast<UTMMACanonDataAsset>(EnemyDataAsset)) {
		CanonDataAsset = CastedCanonDataAsset;
		CanonShotType = CanonDataAsset->CanonShotType;
		PatternCountChangeMod = CanonDataAsset->PatternCountState.PatternCountChangeMod;
		PatternCountEndCount = CanonDataAsset->PatternCountState.PatternCountEndCount;
	}
	float FunctionTime = 0.2f;
	FTimerHandle _TimerHandle;
	// ショットを放つ種類によって、発射開始距離等を設定.
	switch (CanonShotType)
	{
	case ECanonShotType::Shot:
		RecentlyRenderedLerance = 0.2f;
		PlusDistance = 1000.0f;
		MinusDistance = -500.0f;
		GetWorldTimerManager().SetTimer(_TimerHandle, this, &ATMMACanonEnemy::ShotBulletTypeShot, FunctionTime, true);
		break;
	case ECanonShotType::Laser:
		RecentlyRenderedLerance = 0.0f;
		PlusDistance = 10.0f;
		MinusDistance = -10.0f;
//		FunctionTime = 0.1f;
//		GetWorldTimerManager().SetTimer(_TimerHandle, this, &ATMMACanonEnemy::ShotBulletTypeLaser, FunctionTime, true);
		break;
	default:
		break;
	}
}

void ATMMACanonEnemy::FunctionByTimerEvent()
{
	switch (CanonShotType) {
	case ECanonShotType::Shot:
		if (WasRecentlyRendered(RecentlyRenderedLerance) && GetInDistanceAtPlayerY(PlusDistance, MinusDistance)) {
			CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
		}
		break;
	case ECanonShotType::Laser:
		if (ShotTime <= MaxShotTime) {
			ShotTime += 0.1f;
		}
		ShotBulletTypeLaser();
		break;
	}
}

void ATMMACanonEnemy::ShotBulletTypeShot()
{
	if (WasRecentlyRendered(RecentlyRenderedLerance) && GetInDistanceAtPlayerY(PlusDistance, MinusDistance)) {
		switch (PatternType)
		{
			case 0:
				InVector = FVector(0.0f, -1.0f, 1.0f);
				break;
			default:
				FVector PlayerLotation;
				UTMMAActorLibrary::GetPlayerLocation(PlayerLotation);
				InVector = PlayerLotation;
				break;
		}
		AActor* SpawnShot;
		ShotEnemyBulletXVectorByIndex(FVector(0.0f, 0.0f, 0.0f), InVector, 0, FVector(0.3f, 0.3f, 0.3f), SpawnShot);
	}
}

void ATMMACanonEnemy::ShotBulletTypeLaser()
{
	if (WasRecentlyRendered(RecentlyRenderedLerance) && GetInDistanceAtPlayerZ(PlusDistance, MinusDistance)) {
		InVector = FVector(0.0f, -1.0f, 1.0f);
		FVector StartVector = FVector(0.0f, 0.0f, 0.0f);
		FVector ScaleVector = FVector(0.3f, 0.3f, 1.0f);
		StartVector.Z += 50.0f;
		AActor* SpawnLaser;
		bool IsCombineShotTime = false;
		if (BorderShotTime > ShotTime) {
			IsCombineShotTime = true;
		}
		ShotBulletForXVectorByShotTime(StartVector, InVector, ShotEnemyBulletList[0], ScaleVector, IsCombineShotTime, SpawnLaser);
		if (IsValid(SpawnLaser)) {
			SpawnLaser->AddActorLocalRotation(FRotator(90.0f, 0.0f, 0.0f));
		}
	}
}

void ATMMACanonEnemy::ShotBulletForXVectorByShotTime(FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, bool IsCombineShotTime, AActor*& SpawnShot)
{
	FRotator LookAtRotation = TargetVector.Rotation();
	LookAtRotation.Roll = 0.0f;
	if (IsCombineShotTime) {
		LookAtRotation.Roll += ((ShotTime - BorderShotTime) * -60.0f);
	}
	FVector RoVector = LookAtRotation.RotateVector(StartVector);
	// 引数の各値で0以下ののものはデフォルトの1に設定。
	if (InScale.X <= 0.0) {
		InScale.X = 1.0;
	}
	if (InScale.Y <= 0.0) {
		InScale.Y = 1.0;
	}
	if (InScale.Y <= 0.0) {
		InScale.Y = 1.0;
	}
	FVector PlayerStartLocation = GetActorLocation();
	PlayerStartLocation.Z += 50.0f;
	FTransform ShotTransform = UKismetMathLibrary::MakeTransform((PlayerStartLocation + RoVector), LookAtRotation, InScale);
	if (BulletActor != nullptr) {
		AActor* ShotActor = GetWorld()->SpawnActor<AActor>(BulletActor, ShotTransform);
		//		if (IsValid(ShotActor)) {
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(ShotActor) == true) {
			ShotActor->SetActorTransform(ShotTransform);
			SpawnShot = ShotActor;
		}
		else {
			SpawnShot = nullptr;
		}
	}
	else {
		SpawnShot = nullptr;
	}

}
