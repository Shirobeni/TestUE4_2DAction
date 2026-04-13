// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAGoblinEnemyBase.h"
#include "TestMyMakeAction/Library/TMMAProjectileUtil.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ATMMAGoblinEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	// 共通敵AIクラスへキャストして設定
	if (ATMMAEnemyAiBase* CastedMultiEnemyAI = Cast<ATMMAEnemyAiBase>(GetController())) {
		MultiEnemyAI = CastedMultiEnemyAI;
		// 距離制限なしに設定
		MultiEnemyAI->SetIsUnlimitedDistance(true);
	}
	// データアセットのキャスト
	if (!EnemyDataAsset) return;
	if (UTMMAGoblinEnemyDataAsset* CastedGoblinDataAsset = Cast<UTMMAGoblinEnemyDataAsset>(EnemyDataAsset))
	{
		GoblinDataAsset = CastedGoblinDataAsset;
		// マテリアルをメッシュに設定
		USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		if (MeshComponent) {
			for (int idx = 0; idx < SkeltalMaterialArray.Num(); idx++) {
				if (!SkeltalMaterialArray[idx]) continue;
				MeshComponent->SetMaterial(idx, SkeltalMaterialArray[idx]);
			}
		}
	}
}

void ATMMAGoblinEnemyBase::FunctionByTimerEvent()
{
	Super::FunctionByTimerEvent();
	switch (GoblinDataAsset->GetAttackType()) {
		default:
			break;
		case EAttackType::ShotBullet:
		case EAttackType::ThrowKnife:
			MoveAndShot();
			break;
		case EAttackType::ThrushKnife:
			MoveAndThrush();
			break;
		case EAttackType::ThrowRoller:
		case EAttackType::ThrowGrenade:
			ThrowAndStand();
			break;
	}
}

void ATMMAGoblinEnemyBase::MoveAndShot()
{
	ShotDelayFloat = 0.5f;
	if (GetInDistanceAtPlayerY(100.0f, -200.0f)) {
		IsUnlockAbleMoveDoOnce = true;
		IsLockAbleMoveDoOnce = false;
		MultiEnemyAI->SetIsAbleMove(true);
		ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
			ShotBulletOrKnife();
		});
	}
	else
	{
		IsUnlockAbleMoveDoOnce = false;
		IsLockAbleMoveDoOnce = true;
		MultiEnemyAI->SetIsAbleMove(false);
	}
}

void ATMMAGoblinEnemyBase::MoveAndThrush()
{
	if (GetInDistanceAtPlayerY(500.0f, -500.0f)) {
		ShotDelayFloat = 0.4f;
		ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
			ShotBulletOrKnife();
		});
	}
}

void ATMMAGoblinEnemyBase::ThrowAndStand()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	PlayerLocation.Y -= 100.0f;
	PlayerLocation.Z += 50.0f;
	
}

void ATMMAGoblinEnemyBase::ShotBulletOrKnife()
{
	FVector StartVector = FVector(1.0f, 1.0f, 1.0f);
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	AActor* SpawnShot;
	// 攻撃方法によって処理を変える
	switch (GoblinDataAsset->GetAttackType()) {
	default:
		break;
	case EAttackType::ShotBullet:
		ScaleVector = FVector(0.3f, 0.3f, 0.3f);
		ShotEnemyBulletAimByIndex(StartVector, PlayerLocation, 0, ScaleVector, SpawnShot);
		break;
	case EAttackType::ThrowKnife:
		ScaleVector = FVector(0.1f, 0.1f, 0.1f);
		ShotEnemyBulletAimByIndex(StartVector, PlayerLocation, 0, ScaleVector, SpawnShot);
		break;
	case EAttackType::ThrushKnife:
		StartVector = FVector(0.0f, 0.0f, 0.0f);
		ScaleVector = FVector(0.1f, 0.1f, 0.1f);
		ShotEnemyBulletAimByIndex(StartVector, PlayerLocation, 0, ScaleVector, SpawnShot);
	case EAttackType::ThrowRoller:
	case EAttackType::ThrowGrenade:
		StartVector = FVector(0.0f, 0.0f, 0.0f);
		PlayerLocation.Y -= 100.0f;
		PlayerLocation.Z += 50.0f;
		ShotEnemyBulletAimByIndex(StartVector, PlayerLocation, 0, ScaleVector, SpawnShot);
		if (!SpawnShot) break;
		if (GoblinDataAsset->GetAttackType() == EAttackType::ThrowGrenade) {
			if (ATMMAEnemyBulletBase* CastedEnemyBullet = Cast<ATMMAEnemyBulletBase>(SpawnShot)) {
				UTMMAProjectileUtil::MultiplyVelocity(CastedEnemyBullet->GetProjectileMovement(), 0.0f, 10.0f, 30.0f);
				CastedEnemyBullet->GetProjectileMovement()->ProjectileGravityScale = 2.0f;
			}
		}
		else {
			SpawnShot->AddActorWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
		}
	}
}
