// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMMAEnemyAiBase.h"
#include "TestMyMakeAction/Actor/Enemy/TMMABoss7Base.h"
#include "TMMABoss7AiBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMABoss7AiBase : public ATMMAEnemyAiBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	
private:
	ATMMABoss7Base* Boss7;
};
