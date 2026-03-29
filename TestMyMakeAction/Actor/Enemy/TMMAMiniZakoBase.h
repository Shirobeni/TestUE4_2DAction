// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/TMMAEnemyBase.h"
#include "TestMyMakeAction/Ai/TMMAEnemyAiBase.h"
#include "TestMyMakeAction/DataAsset/Enemy/MiniZako/TMMAMiniZakoEnemyDataAsset.h"
#include "TMMAMiniZakoBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAMiniZakoBase : public ATMMAEnemyBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	void SpawnShotFunction();
	 
	void SetMiniZakoAsset();

	UFUNCTION(BlueprintCallable)
	virtual void FunctionByTimerEvent() override;

	UFUNCTION(BlueprintPure)
	ATMMAEnemyAiBase* GetEnemyAi() const
	{
		return EnemyAi;
	}

	UFUNCTION(BlueprintCallable)
	void SetReloadAssetFlag(bool InReloadAssetFlag);

	UFUNCTION(BlueprintCallable)
	void SetSoftDataAsset(TSoftObjectPtr<UTMMAEnemyDataAsset> InDataAsset);

protected:
     ESpawnShotType MiniZakoShotType;

	 ATMMAEnemyAiBase* EnemyAi;

	 bool ReloadAssetFlag;

	 bool AssetDoOnceFlag = true;

};
