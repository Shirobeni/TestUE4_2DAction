// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TMMAItemDataAsset.generated.h"

UENUM()
enum class EAssetItemType : uint8
{
	PowerUp UMETA(DisplayName = "PowerUp"),
	ChangeRapid UMETA(DisplayName = "ChangeRapid"),
	ChangeHoming UMETA(DisplayName = "ChangeHoming"),
	ChangeFire UMETA(DisplayName = "ChangeFire"),
	ChangeGrenade UMETA(DisplayName = "ChangeGrenade"),
	ChangeLaser UMETA(DisplayName = "ChangeLaser"),
	GetBurst UMETA(DisplayName = "GetBurst"),
	LifeUp UMETA(DisplayName = "LifeUp")
};

UENUM()
enum class EAssetChangeWeaponType : uint8
{
	Rapid UMETA(DisplayName = "Rapid"),
	Homing UMETA(DisplayName = "Homing"),
	Fire UMETA(DisplayName = "Fire"),
	Grenade UMETA(DisplayName = "Grenade"),
	Laser UMETA(DisplayName = "Laser"),
	None UMETA(DisplayName = "None")
};

UCLASS()
class TESTMYMAKEACTION_API UTMMAItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	const EAssetItemType GetItemType() const
	{
		return ItemType;
	}

	const EAssetChangeWeaponType GetChangeWeaponType() const
	{
		return ChangeWeaponType;
	}
	
	TSoftObjectPtr<USoundBase> GetSoftGettedSound() const
	{
		return SoftGettedSound;
	}

	TSoftObjectPtr<UMaterial> GetSoftBoxMaterial() const
	{
		return SoftBoxMaterial;
	}

	TSoftObjectPtr<UStaticMesh> GetSoftIconCharMesh() const
	{
		return SoftIconCharMesh;
	}

	FVector GetAssetAddLocationParamForChar() const
	{
		return AddLocationParamForChar;
	}

	FRotator GetAssetAddRotationParamForChar() const
	{
		return AddRotationParamForChar;
	}

	FVector GetAssetScaleVectorForChar() const
	{
		return ScaleVectorForChar;
	}

public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	EAssetItemType ItemType = EAssetItemType::PowerUp;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	EAssetChangeWeaponType ChangeWeaponType = EAssetChangeWeaponType::Rapid;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundBase> SoftGettedSound;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	TSoftObjectPtr<UMaterial> SoftBoxMaterial;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMesh> SoftIconCharMesh;

	/**
	 * --------------------------------------------------------------------- 
	 * アイテムアイコン文字調整用パラメータ
	 * モデリング側であらかじめした方が望ましいが…出来なかったときのために
	 * ---------------------------------------------------------------------
	 */
	// 位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector AddLocationParamForChar;

	// 角度
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator AddRotationParamForChar;

	// サイズ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector ScaleVectorForChar;
};
