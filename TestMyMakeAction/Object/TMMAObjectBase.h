// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestMyMakeAction/Actor/TMMAActorBase.h"
#include "TMMAObjectBase.generated.h"

UCLASS()
class TESTMYMAKEACTION_API ATMMAObjectBase : public ATMMAActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMMAObjectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetSwitchFlag(bool InSwitchFlag);

	UFUNCTION(BlueprintPure)
		const bool GetSwitchFlag() const
	{
		return SwitchFlag;
	}

	UFUNCTION(BlueprintCallable)
		void InitMoveTime();

	UFUNCTION(BlueprintCallable)
		void AddMoveTime(float InMoveTime);

	UFUNCTION(BlueprintPure)
		const float GetMoveTime() const
	{
		return MoveTime;
	}
	
	UFUNCTION(BlueprintCallable)
		void SetLimitMoveTime(float InLimitMoveTime);

	UFUNCTION(BlueprintPure)
		const float GetLimitMoveTime() const
	{
		return LimitMoveTime;
	}


public:
	UPROPERTY(BlueprintReadWrite)
		bool SwitchFlag = false;

	UPROPERTY(BlueprintReadWrite)
		float MoveTime = 0.0;

	UPROPERTY(BlueprintReadWrite)
		float LimitMoveTime = 0.0;

};
