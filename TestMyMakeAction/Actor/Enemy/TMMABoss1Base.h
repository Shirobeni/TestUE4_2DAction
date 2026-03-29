// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TMMABoss1Base.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMABoss1Base : public ATMMAEnemyBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;
	
	// ボスの行動関連
	void BossAction();
	
	void ShotPattern1();
	
	void ShotPattern2();

	void ShotPattern3();

	void ShotPattern4();

protected:
	FVector InVector = FVector(0.0f, 0.0f, 0.0f);
	
private:
	float ShotFloat = 0.0f;

	float ShotDelayFloat = 0.0f;

};
