// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TMMASemiBoss4Base.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMASemiBoss4Base : public ATMMAEnemyBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

private:
	void BossAction();

	void ShotEnemyBullet2Way();

	void ShotEnemyBulletWay();

	void ShotDestroyableBulletWay();

	void ShotMissile();

private:
	float ShotFloat1 = 0.0f;
	
	float ShotDelayFloat1 = 0.1f;

	float ShotFloat2 = 0.0f;

	float ShotDelayFloat2 = 0.5f;
};
