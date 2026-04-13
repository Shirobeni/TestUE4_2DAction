// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TMMASemiBoss2Base.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMASemiBoss2Base : public ATMMAEnemyBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

	UFUNCTION(BlueprintCallable)
	void SetMissileCannonComponent(USkeletalMeshComponent* InMissileCannonComponent);

	UFUNCTION(BlueprintCallable)
	void SetCannonComponent(USkeletalMeshComponent* InCannonComponent);
	
private:
	void ShotRapidEnemyBullet();

	void ShotMissile();

	void InstantAnimation();

private:
	USkeletalMeshComponent* MissileCannonComponent;

	USkeletalMeshComponent* CannonComponent;

	int BulletCount = 0;

	int AbleBulletCount = 10;

	int MaxBulletCount = 20;

	float ShotFloat = 0.0f;

	float ShotDelayFloat = 0.1f;

	float MissileFloat = 0.0f;

	float MissileDelayFloat = 0.3f;
};
