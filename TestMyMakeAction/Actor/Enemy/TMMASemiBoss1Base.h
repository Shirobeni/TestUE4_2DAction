// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TestMyMakeAction/AI/TMMAEnemyAiBase.h"
#include "TMMASemiBoss1Base.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMASemiBoss1Base : public ATMMAEnemyBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

private:
	void ShotEnemyBullet();

	void ShotEnemyMissile();

protected:
	ATMMAEnemyAiBase* EnemyAi;

	int ShotCount = 0;

	int ShotAbleCount = 30;

	int MaxShotCount = 50;

	float ShotFloat = 0.0f;

	float ShotDelayFloat = 0.2f;

	float MissileFloat = 0.0f;

	float MissileDelayFloat = 1.0f;
};
