// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMMAEnemyAiBase.h"
#include "TestMyMakeAction/TestMyMakeActionGameModeBase.h"
#include "TestMyMakeAction/Actor/Enemy/TMMABoss6Base.h"
#include "TMMABoss6AiBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMABoss6AiBase : public ATMMAEnemyAiBase
{
	GENERATED_BODY()

public:
	const int GetDestinationIndex() const
	{
		return DestinationIndex;
	}

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void PopDestinationLocation();

	void MovePatroll();

	void AddAttackintTime();

	void SetDestinationVector();

	void InitDestinationIndexForDelay();

private:
	ATMMABoss6Base* Boss6;

	TArray<AActor*> DestinationPointActorListPt1;

	TArray<AActor*> DestinationPointActorListPt2;

	AActor* TargetDestinationPointActor;

	int DestinationIndex = 0;

	ATestMyMakeActionGameModeBase* MainGameMode;

	FVector DestinationVector = FVector(0.0f, 0.0f, 0.0f);
	
	float DelicadeTime = 0.0f;

	float AttackingTime = 0.0f;

	FTimerHandle TimerHandle;

	bool IsTransformDoOnceFlag = false;

};
