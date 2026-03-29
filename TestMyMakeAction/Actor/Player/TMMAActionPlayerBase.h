// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAPlayerBase.h"
#include "TMMAActionPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAActionPlayerBase : public ATMMAPlayerBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	void ShotFunction();
	
	void MissileShotFunc();

	UFUNCTION(BlueprintCallable)
	void SetShotAxisLeftRight(float InShotAxisLeftRight);

	UFUNCTION(BlueprintCallable)
	void SetShotAxisUpDown(float InShotAxisUpDown);

public:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<class ABulletBase> SoftSwordClass;
	
	float ShotAxisLeftRight = 0.0f;
	
	float ShotAxisUpDown = 0.0f;

private:	
	TSubclassOf<ABulletBase> SwordClass;
	
	FTimerHandle Handle;

};
