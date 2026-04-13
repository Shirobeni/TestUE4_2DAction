// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/DataAsset/Enemy/TMMAEnemyDataAsset.h"
#include "TMMAEyesEnemyDataAsset.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EEyesEnemyCategotyType : uint8
{
	Laser UMETA(DisplayName = "Laser"),
	Shot UMETA(DisplayName = "Shot")
};
 
UCLASS()
class TESTMYMAKEACTION_API UTMMAEyesEnemyDataAsset : public UTMMAEnemyDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	EEyesEnemyCategotyType CategoryType;
};
