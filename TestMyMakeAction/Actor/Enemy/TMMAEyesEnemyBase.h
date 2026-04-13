// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TestMyMakeAction/DataAsset/Enemy/Eyes/TMMAEyesEnemyDataAsset.h"
#include "TMMAEyesEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAEyesEnemyBase : public ATMMAEnemyBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent();

	UFUNCTION(BlueprintCallable)
	void SetProjectileMovementComp(UProjectileMovementComponent* InProjectileMovementComp);

private:
	// レーザータイプ時の行動
	void ActionTypeLaser();

	// ショットタイプ時の行動
	void ActionTypeShot();

	void Shot();

	// プレイヤーキャラクターに対してホーミングを設定する.
	void SetHomingToPlayer();

private:
	UProjectileMovementComponent* ProjectileMovementComp;

	UTMMAEyesEnemyDataAsset* EyesEnemyDataAsset;
	
	int ShotAbleCount = 0;

	float ShotFloat = 0.0f;

	float ShotDelayFloat = 0.0f;

	FVector InVector = FVector(0.0f, 0.0f, 0.0f);

};
