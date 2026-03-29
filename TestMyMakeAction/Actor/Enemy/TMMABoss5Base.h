// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TMMABoss5Base.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMABoss5Base : public ATMMAEnemyBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;
	
private:
	void BossAttack();

	void ShotMissile();
	
	void ShotReverseMissile();
	
	void ShotDestroyableBullet();

	void ShotEnemyWayBullet();
	
private:
	bool IsMoveUp = false;
	
	FTimerHandle TimerHandle;

	float ShotFloat = 0.0f;

	float ShotDelayFloat = 0.0f;
};
