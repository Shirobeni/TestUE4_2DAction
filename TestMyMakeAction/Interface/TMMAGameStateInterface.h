// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TMMAGameStateInterface.generated.h"

/**
 *
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UGameStateInterface : public UInterface
{
	GENERATED_BODY()
};

class IGameStateInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AddScore")
	void AddEnemyScore(int InBaseScore);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AddScore")
	void AddEnemyScoreByDiff(int InBaseScore);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AddScore")
	void AddItemScore(int InBaseScore);

};

/**
 * 
 */
class TESTMYMAKEACTION_API TMMAGameStateInterface
{
public:
	TMMAGameStateInterface();
	~TMMAGameStateInterface();
};
