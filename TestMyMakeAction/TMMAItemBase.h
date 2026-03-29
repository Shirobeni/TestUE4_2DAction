// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "TestMyMakeAction/Actor/TMMAActorBase.h"
#include "TMMAPlayerBase.h"
#include "TMMAGetItemActor.h"
#include "TestMyMakeAction/DataAsset/Item/TMMAItemDataAsset.h"
#include "TMMAItemBase.generated.h"

USTRUCT()
struct FItemTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	// アイテム名
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = ItemRowStruct)
	FName ItemName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = ItemRowStruct)
	FName ItemCategoryName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = ItemRowStruct)
	FName ChangeWeapon;

	// ※パスについては、ディレクトリの始まりがContentからなので、その次のディレクトリから記入する.
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = ItemRowStruct)
	FString SoundPath;

};

/**
 *
 */
UENUM()
enum class EItemType : uint8
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
enum class EChangeWeaponType : uint8
{
	Rapid UMETA(DisplayName = "Rapid"),
	Homing UMETA(DisplayName = "Homing"),
	Fire UMETA(DisplayName = "Fire"),
	Grenade UMETA(DisplayName = "Grenade"),
	Laser UMETA(DisplayName = "Laser"),
	None UMETA(DisplayName  = "None")
};


UCLASS()
class TESTMYMAKEACTION_API ATMMAItemBase : public ATMMAActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMMAItemBase();

	UFUNCTION(BlueprintPure)
	const FString GetCurrentLevelName() const
	{
		return CurrentLevelName;
	}

	UFUNCTION(BlueprintCallable)
	void SetStatusByAsset();

	// アイテムキャリア用
	UFUNCTION(BlueprintCallable)
	void SetSoftItemAsset(TSoftObjectPtr<UTMMAItemDataAsset> InSoftItemAsset);

	UFUNCTION(BlueprintCallable)
	void SetReloadAssetFlag(bool InReloadAsset);

	UFUNCTION(BlueprintPure)
	const bool GetReloadAssetFlag() const
	{
		return ReloadAssetFlag;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetStatusByTable(FName TableRow);

	UFUNCTION(BlueprintCallable)
	void PlayItemGetSound();

	// アイテム取得時の処理
	UFUNCTION(BlueprintCallable)
	void ItemGet(AActor* InPlayerActor, AActor* InGetItemActor);

	// 各アイテムごとの取得処理
	void PlayerPowerUp(ATMMAPlayerBase* InPlayerActor, ATMMAGetItemActor* InGetItemActor);

	void ChangeWeapon(ATMMAPlayerBase* InPlayerActor, ATMMAGetItemActor* InGetItemActor);

	void AddBurst(ATMMAPlayerBase* InPlayerActor, ATMMAGetItemActor* InGetItemActor);

	void AddPlayerLife(ATMMAPlayerBase* InPlayerActor, ATMMAGetItemActor* InGetItemActor);

	UFUNCTION(BlueprintPure)
	UMaterial* GetBoxMaterilal() const
	{
		return BoxMaterial;
	}

	UFUNCTION(BlueprintPure)
	UStaticMesh* GetIconCharMesh() const
	{
		return IconCharMesh;
	}

	UFUNCTION(BlueprintPure)
	FVector GetAddLocationParamForChar() const
	{
		return AddLocationParamForChar;
	}

	UFUNCTION(BlueprintPure)
	FRotator GetAddRotationParamForChar() const
	{
		return AddRotationParamForChar;
	}

	UFUNCTION(BlueprintPure)
	FVector GetScaleVectorForChar() const
	{
		return ScaleVectorForChar;
	}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTMMAItemDataAsset> SoftItemDataAsset;

	FItemTableRow ItemTableRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* ItemDataTable;


private:
	USoundBase* GetItemSound;

	FString CurrentLevelName = FString::Printf(TEXT("Stage0"));

	FName ItemName;

	FName WeaponCategory;

	FName ItemCategoryName;

	// データアセットでマテリアルやメッシュ等使いまわせるかのテスト実装
	// アイテム種類
	EItemType ItemType = EItemType::PowerUp;

	// チェンジする武器
	EChangeWeaponType ChangeWeaponType = EChangeWeaponType::None;

	// ボックス用マテリアル
	UMaterial* BoxMaterial;

	// アイコン文字用スタティックメッシュ
	UStaticMesh* IconCharMesh;

	// データアセット
	UTMMAItemDataAsset* ItemDataAsset;

	// データアセット再読み込みフラグ ※Stage5 アイテムキャリアに使う
	bool ReloadAssetFlag = false;

/**
 * ---------------------------------------------------------------------
 * アイテムアイコン文字調整用パラメータ
 * モデリング側であらかじめした方が望ましいが…出来なかったときのために
 * ---------------------------------------------------------------------
 */
	// 位置
	FVector AddLocationParamForChar = FVector(0.0f, 0.0f, 0.0f);

	// 角度
	FRotator AddRotationParamForChar = FRotator(0.0f, 0.0f, 0.0f);

	// サイズ
	FVector ScaleVectorForChar = FVector(1.0f, 1.0f, 1.0f);
};
