// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "TMMABulletDataAsset.generated.h"

/**
 * 
 */

UCLASS()
class TESTMYMAKEACTION_API UTMMABulletDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	const int GetDamage() const
	{
		return Damage;
	}

	UFUNCTION(BlueprintPure)
	const int GetAddedDamageParamLv2() const
	{
		return AddedDamageParamLv2;
	}

	UFUNCTION(BlueprintPure)
	const int GetAddedDamageParamLv3() const
	{
		return AddedDamageParamLv3;
	}

	UFUNCTION(BlueprintPure)
	const int GetReloadBullet() const
	{
		return ReloadBullet;
	}

	UFUNCTION(BlueprintPure)
	const int GetReloadBulletTimesLv2() const
	{
		return ReloadBulletTimesLv2;
	}

	UFUNCTION(BlueprintPure)
	const int GetReloadBulletTimesLv3() const
	{
		return ReloadBulletTimesLv3;
	}

	UFUNCTION(BlueprintPure)
	const int GetDeleteTime() const
	{
		return DeleteTime;
	}

	UFUNCTION(BlueprintPure)
	TSoftObjectPtr<USoundBase> GetSoftShotSound() const
	{
		return SoftShotSound;
	}

	UFUNCTION(BlueprintPure)
	const FString GetSoundPath() const
	{
		return SoundPath;
	}

public:
	UPROPERTY(EditAnywhere)
	int Damage;

	UPROPERTY(EditAnywhere)
	int AddedDamageParamLv2;

	UPROPERTY(EditAnywhere)
	int AddedDamageParamLv3;

	UPROPERTY(EditAnywhere)
	int ReloadBullet;

	UPROPERTY(EditAnywhere)
	int ReloadBulletTimesLv2;

	// パワーアップ2段階目時のリロード倍数
	UPROPERTY(EditAnywhere)
	int ReloadBulletTimesLv3;

	UPROPERTY(EditAnywhere)
	float DeleteTime;

	UPROPERTY(EditAnywhere)
	int Score;

	UPROPERTY(EditAnywhere)
	FString SoundPath;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundBase> SoftShotSound;

	USoundBase* ShotSound;

};
