// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TMMAAircraftEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAAircraftEnemyBase : public ATMMAEnemyBase
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;
	
	void ShotFunction1();

	void ShotFunction2();
	
};
