// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TMMABoss4Base.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMABoss4Base : public ATMMAEnemyBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;
	
private:
	void BossAttack();

	void SpawnLaserAndRotate();
	
	void SpawnDestroyableShot();

	void SpawnHomingShot();

	void JumpAttack();
	
private:
	FVector InVector;

	TArray<ATMMAEnemyBulletBase*> RiseSeedBulletList;
	
	float LimitPatternCount = 15.0f;

	int JumpCount = 0;

	// 体当たりでの攻撃状態かどうか
	bool IsAttackable = false;

	// 形態変更用do onceフラグ
	bool TransformDoOnceFlag = false;

	FTimerHandle TimerHandle;

	float ShotFloat = 0.0f;

	float ShotDelayFloat = 0.0f;

};
