// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/DataAsset/Enemy/TMMAEnemyDataAsset.h"
#include "TMMAGoblinEnemyDataAsset.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAttackType : uint8
{
    ShotBullet UMETA(DisplayName="ShotBullet"),
    ThrushKnife UMETA(DisplayName="ThrushKnife"),
	ThrowKnife UMETA(DisplayName="ThrowKnife"), // 対象アクタのサイズが変更できない…のでしばらく。
	ThrowRoller UMETA(DisplayName="ThrowRoller"),
	ThrowGrenade UMETA(DisplayName = "ThrowGrenade"),

};

UCLASS()
class TESTMYMAKEACTION_API UTMMAGoblinEnemyDataAsset : public UTMMAEnemyDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	EAttackType GetAttackType() const
	{
		return AttackType;
	}

public :
	UPROPERTY(EditAnywhere)
	EAttackType AttackType;

};
