// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Library/TMMAActorLibrary.h"
#include "TestMyMakeAction/Actor/TMMAActorBase.h"
#include "TMMAOtherActor.generated.h"

#define DEFAULT_LIVING_TIME 2.0f;

UCLASS()
class TESTMYMAKEACTION_API ATMMAOtherActor : public ATMMAActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATMMAOtherActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddLivingTime(float InLivingTime);

	UFUNCTION(BlueprintPure)
	const float GetLivingTime() const
	{
		return LivingTime;
	}

	UFUNCTION(BlueprintCallable)
	void SetMaxLivingTime(float InMaxLivingTime);

	UFUNCTION(BlueprintPure)
	const float GetMaxLivingTime() const
	{
		return MaxLivingTime;
	}

	UFUNCTION(BlueprintPure)
	const bool GetIsOverLivingTime() const
	{
		bool IsOverLivingTime = false;
		if (LivingTime > MaxLivingTime) {
			IsOverLivingTime = true;
		}
		return IsOverLivingTime;
	}

private:
	float MaxLivingTime = DEFAULT_LIVING_TIME;

	float LivingTime = 0.0f;
};
