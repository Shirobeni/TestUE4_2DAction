// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TestMyMakeAction/AI/TMMAEnemyAiBase.h"
#include "TestMyMakeAction/DataAsset/Enemy/Goblin/TMMAGoblinEnemyDataAsset.h"
#include "TMMAGoblinEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAGoblinEnemyBase : public ATMMAEnemyBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

private:
	void MoveAndShot();

	void ShotBulletOrKnife();

	void MoveAndThrush();

	void ThrowAndStand();

protected:
	// AI
	ATMMAEnemyAiBase* MultiEnemyAI;

	// データアセット(専用)
	UTMMAGoblinEnemyDataAsset* GoblinDataAsset;
	
	bool IsUnlockAbleMoveDoOnce = true;

	bool IsLockAbleMoveDoOnce = false;

	float ShotFloat = 0.0f;
	
	float ShotDelayFloat = 0.0f;
};
