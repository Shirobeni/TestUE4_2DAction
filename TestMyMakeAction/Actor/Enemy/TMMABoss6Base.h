
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TMMABoss6Base.generated.h"

/**
 * 
 */
class ATMMABoss6AiBase;

UCLASS()
class TESTMYMAKEACTION_API ATMMABoss6Base : public ATMMAEnemyBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

private:
	void BossAttack();

	void ShotPatternByPt1();

	void ShotPatternByPt2();

	// BulletIndex : 0
	void ShotEnemyBulletWay();

	// BulletIndex : 1
	void ShotHomingBullet();

	// BulletIndex : 2
	void ShotRiseBulletWay();

	// BulletIndex : 3
	void ShotEnemyDestroyBullet();

	// BulletIndex : 4
	void ShotDestroyableMissile();

	// BulletIndex : 5
	void ShotWinderWay();

public:
	UPROPERTY(EditAnywhere)
	TArray<AActor*> DestinationPointActorListPt1;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> DestinationPointActorListPt2;

private:
	ATMMABoss6AiBase* Boss6AI;

	bool IsTransformDoOnce = false;

	FTimerHandle TimerHandle;
	
	float ShotFloat = 0.0f;

	float ShotDelayFloat = 0.0f;
};

