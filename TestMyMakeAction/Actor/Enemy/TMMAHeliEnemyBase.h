// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "GameFramework/Character.h"
#include "TMMAHeliEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAHeliEnemyBase : public ATMMAEnemyBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AttachChildCompByAsset();

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

	void MoveByAimPlayer();

	void ShotMissile();
};
