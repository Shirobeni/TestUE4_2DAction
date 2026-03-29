// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMYMakeAction/TMMAEnemyBase.h"
#include "TestMyMakeAction/TMMALockCollisionBase.h"
#include "TMMABoss2Base.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMABoss2Base : public ATMMAEnemyBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

	void BossAction();

	UFUNCTION(BlueprintCallable)
	void SetLegCannonComponents(TArray<USceneComponent*> InLegCannonComponents);

	void ChangeTransform();

	// 第2形態移行時に地上移動へ
	void MoveGround();

	// ショット攻撃関連
	void AimShotByLeg();

	void ShotLaser();

public:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<ATMMALockCollisionBase> SofBossLockCollisionClass;

private:
	TArray<USceneComponent*> LegCannonComponents;

	bool IsTransformChangeDoOnce = false;

	ATMMALockCollisionBase* BossLockCollision;

	FTimerHandle TimerHandle;

	float ShotFloat = 0.0f;

	float ShotDelayFloat = 0.0f;
};
