// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/DataAsset/Enemy/TMMAEnemyDataAsset.h"
#include "TMMACanonDataAsset.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class ECanonShotType : uint8
{
	Shot UMETA(DisplayName = "Shot"),
	Laser UMETA(DisplayName = "Laser")
};

USTRUCT(BlueprintType)
struct FPatternCountState
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	int PatternCountChangeMod;

	UPROPERTY(EditAnywhere)
	int PatternCountEndCount;

};

UCLASS()
class TESTMYMAKEACTION_API UTMMACanonDataAsset : public UTMMAEnemyDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	ECanonShotType CanonShotType;

	UPROPERTY(EditAnywhere)
	FPatternCountState PatternCountState;
};
