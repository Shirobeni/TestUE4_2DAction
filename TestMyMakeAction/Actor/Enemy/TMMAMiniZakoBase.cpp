// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAMiniZakoBase.h"

void ATMMAMiniZakoBase::BeginPlay()
{
	Super::BeginPlay();
	SetMiniZakoAsset();
	// AI設定
	if (ATMMAEnemyAiBase* CastedEnemyAi = Cast<ATMMAEnemyAiBase>(GetController())) {
		EnemyAi = CastedEnemyAi;
		EnemyAi->SetIsUnlimitedDistance(true);
		UE_LOG(LogTemp, Log, TEXT("Success Casted %s"), *EnemyAi->GetName());
	}
	// ショットのタイマー設定
	FTimerHandle _TimerHandle;
	GetWorldTimerManager().SetTimer(_TimerHandle, this, &ATMMAMiniZakoBase::SpawnShotFunction, 1.0f, true);
}

void ATMMAMiniZakoBase::SetMiniZakoAsset()
{
	// 専用アセットより、ステータスを設定.
	if (UTMMAMiniZakoEnemyDataAsset* MiniZakoDataAsset = Cast<UTMMAMiniZakoEnemyDataAsset>(EnemyDataAsset)) {
		MiniZakoShotType = MiniZakoDataAsset->AssetShotType;
	}
}

void ATMMAMiniZakoBase::FunctionByTimerEvent()
{
	
	if (ReloadAssetFlag && AssetDoOnceFlag) {
		SetMiniZakoAsset();
		ReloadAssetFlag = false;
		AssetDoOnceFlag = false;
	}
	if (EnemyAi != nullptr && IsValid(EnemyAi)) {
		if (GetInDistanceAtPlayerY(100, -200)) {
			EnemyAi->SetIsAbleMove(true);
		}
		else {
			EnemyAi->SetIsAbleMove(false);
		}
	}
	
}

void ATMMAMiniZakoBase::SpawnShotFunction()
{
	FVector TargetVector = FVector(0.0f, 0.0f, 0.0f);
	UTMMAActorLibrary::GetPlayerLocation(TargetVector);
	FVector BulletScale = FVector(0.3, 0.3, 0.3);
	if (MiniZakoShotType == ESpawnShotType::Laser) {
		BulletScale = FVector(1.0f, 1.0f, 1.0f);
	}
	AActor* SpawnActor;
	ShotEnemyBulletAimByIndex(FVector(0.0f, 0.0f, 0.0f), TargetVector, 0, BulletScale, SpawnActor);
	if (MiniZakoShotType == ESpawnShotType::Laser) {
		// レーザー敵は発射した弾を横にする.
		SpawnActor->AddActorLocalRotation(FRotator(90.0f, 0.0f, 0.0f));
	}
}

void ATMMAMiniZakoBase::SetReloadAssetFlag(bool InReloadAssetFlag)
{
	ReloadAssetFlag = InReloadAssetFlag;
}

void ATMMAMiniZakoBase::SetSoftDataAsset(TSoftObjectPtr<UTMMAEnemyDataAsset> InDataAsset)
{
	SoftEnemyDataAsset = InDataAsset;
	EnemyDataAsset = SoftEnemyDataAsset.LoadSynchronous();
}