// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMMAGeneratorBase.h"
#include "TestMyMakeAction/DataAsset/Enemy/MiniZako/TMMAMiniZakoEnemyDataAsset.h"
#include "TMMAMiniZakoGeneratorBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAMiniZakoGeneratorBase : public ATMMAGeneratorBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	TSoftObjectPtr<UTMMAEnemyDataAsset> GetSoftMiniZakoDataAsset() const
	{
		return SoftMiniZakoDataAsset;
	}


public:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTMMAMiniZakoEnemyDataAsset> SoftMiniZakoDataAsset;

protected:
	UTMMAMiniZakoEnemyDataAsset* MiniZakoDataAsset;
};
