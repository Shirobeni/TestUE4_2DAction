// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TMMAEnemyActorBulletInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UEnemyActorAndBulletInterface : public UInterface
{
	GENERATED_BODY()
};

class IEnemyActorAndBulletInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyActorStatus")
	void Damage(int InDamage, bool IsTimes);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyActorStatus")
	void Score(int InScore);

};

/*
class TESTMYMAKEACTION_API TMMAEnemyActorBulletInterface
{
public:
	TMMAEnemyActorBulletInterface();
	~TMMAEnemyActorBulletInterface();
};
*/

