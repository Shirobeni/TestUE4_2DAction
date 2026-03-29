// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/DataAsset/Enemy/TMMAEnemyDataAsset.h"
#include "TMMAMiniZakoEnemyDataAsset.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESpawnShotType : uint8
{
	Bullet UMETA(DisplayName="Bullet"),
	Laser UMETA(DisplayName="Laser"),
};

UCLASS()
class TESTMYMAKEACTION_API UTMMAMiniZakoEnemyDataAsset : public UTMMAEnemyDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESpawnShotType AssetShotType;
};
