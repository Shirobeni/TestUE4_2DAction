// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TestMyMakeAction/DataAsset/Enemy/Canon/TMMACanonDataAsset.h"
#include "TMMACanonEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMACanonEnemy : public ATMMAEnemyBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

	void ShotBulletTypeShot();

	void ShotBulletTypeLaser();

	void ShotBulletForXVectorByShotTime(FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, bool IsCombineShotTime, AActor*& SpawnShot);

protected:
	UFUNCTION(BlueprintPure)
	ECanonShotType GetCanonShotType() const
	{
		return CanonShotType;
	}

private:
	float RecentlyRenderedLerance = 0.0f;

	float PlusDistance = 1000.0f;

	float MinusDistance = -500.0f;


	/********************************************/
	// ショットタイム関連(レーザーショットに使用する)
	float ShotTime = 0.0;

	float BorderShotTime = 15.0f;

	float MaxShotTime = 15.7f;
	/********************************************/

	FVector InVector;

	ECanonShotType CanonShotType = ECanonShotType::Shot;

	UTMMACanonDataAsset* CanonDataAsset;

};
