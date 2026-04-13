// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAPlayerBase.h"
#include "TMMAShootingPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAShootingPlayerBase : public ATMMAPlayerBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetIsPussingMissileButton(bool InIsPussingMissileButton);
	
private:
	// ƒVƒ‡ƒbƒg”­ŽË
	void ShotFunction();

	void MissileShotOfFunc();

private:
	bool IsPussingMissileButton = false;

	float MissileFloat = 0.0f;

	float MissileDelecateFloat = 3.0f;


};
