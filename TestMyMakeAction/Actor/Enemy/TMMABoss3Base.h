// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TestMyMakeAction/Library/TMMAProjectileUtil.h"
#include "TMMABoss3Base.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMABoss3Base : public ATMMAEnemyBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;
	
	UFUNCTION(BlueprintCallable)
	void SetLanceComponent(USceneComponent* InLanceComponent);
	
	UFUNCTION(BlueprintCallable)
	void SetSceneLanceComp(USceneComponent* InSceneLanceComp);
		
	UFUNCTION(BlueprintCallable)
	void SetBaseSceneComponent(USceneComponent* InBaseSceneComponent);

	void BossAttack();
	
	void LanceAngleShot();
	
	void MoveLanceRotate();

	// ëÑçUåÇ
	void LanceAttack();

	// ÉOÉåÉlÅ[ÉhägéUî≠éÀ
	void SpreadShot();

	void SpredShotByPt2();
private:
	int LanceTimeCount = 0;
	
	USceneComponent* BaseSceneComponent;

	USceneComponent* LanceComponent;
	
	USceneComponent* SceneLanceComp;
	
	FVector InVector;
	
	bool TransformChangeOnceFlag = false;

	FTimerHandle TimerHandle;

	float ShotFloat = 0.0f;

	float ShotDelayFloat = 0.0f;


};
