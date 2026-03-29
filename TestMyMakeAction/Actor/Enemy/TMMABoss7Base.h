
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TestMyMakeAction/Actor/TMMAEnemyPatrollPoint.h"
#include "TMMABoss7Base.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMABoss7Base : public ATMMAEnemyBase
{
	GENERATED_BODY()
	
public:
	ATMMABoss7Base();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

	void SetPatrollPoint();

	// 形態変更時の攻撃待機設定用フラグ
	void SetIsWait(bool InIsWait);

private:
	// パターン用カウントの回転
	void CountingPatternCoundGrandBoss7();

	// 形態変化処理
	void TransformChange();

	// 各種形態の攻撃用メソッド
	void BossTransform1();

	void BossTransform2();

	void BossTransform3();

	void BossTransform4();

	// 各種攻撃メソッド
	// 第一形態1
	void ShotLaserAndMove();

	void ShotDestroyHoming();

	// 第二形態
	void JumpKick();

	void SpawnForceBullet();

	// 第三形態
	void SpawnDestroyShot();

	void SpawnThunderShot();

	void SpawnThunderParticle();

	void SpawnThunderLaser();

	// 第四形態
	void SpawnEnemyBullet();

	void SpawnEnemyHomingMissile();

	void SpawnEnemyFire();

public:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<ATMMAEnemyPatrollPoint> SoftPatrollPoint1;

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<ATMMAEnemyPatrollPoint>> SoftPatrollPoint2List;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UParticleSystem> SoftThunderParticle;

	// ソースコード上で行うため
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	// BossTransform2()用
	bool IsMoveToPtPoint2DoOnce = false;

	// BossTransform3()用
	bool IsMoveToPtPoint1DoOnce = false;


protected:
	TArray<UParticleSystemComponent*> LaserParticleList;

	TArray<FVector> LaserVectorList;

	ATMMAEnemyPatrollPoint* PatrollPoint1;

	TArray<ATMMAEnemyPatrollPoint*> PatrollPoint2List;


private:
	// 形態変更時の攻撃待機設定用フラグ
	bool IsWait = true;

	// 攻撃判定フラグ(敵に触れるとダメージ喰らうフラグ)
	bool AttackFlag = false;

	// サンダーレーザー攻撃用パーティクル
	UParticleSystem* ThunderParticle;

	/* -------------------------------
	 * DoOnceに該当するフラグ
	 * ------------------------------- */
	
	// BossTransform1()用
	bool IsHomingLaserDoOnce = false;

	bool IsJumpAndSpawnDoOnce = false;

	bool IsForceBulletSpawnDoOnce = false;

	bool IsSpawnLaserParticleDoOnce = false;

	bool IsSpawnThunderLaserDoOnce = false;

	// タイマー(2つ目以降は第4形態で使用する.)
	FTimerHandle Handle;

	FTimerHandle HandleSecond;

	FTimerHandle HandleThird;
	
	float FirstShotFloat = 0.0f;
	
	float SecondShotFloat = 0.0f;
	
	float ThirdShotFloat = 0.0f;

	float FirstShotDelayFloat = 0.0f;

	float SecondShotDelayFloat = 0.0f;
	
	float ThirdShotDelayFloat = 0.0f;
};
