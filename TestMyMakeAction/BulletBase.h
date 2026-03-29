// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/DataTable.h"
#include "TMMAPlayerBase.h"
#include "TMMAEnemyActorBulletInterface.h"
#include "TestMyMakeActionGameModeBase.h"
#include "GameState/TMMAGameStateBase.h"
#include "DataAsset/TMMABulletDataAsset.h"
#include "Library/TMMAProjectileUtil.h"
#include "Library/TMMAActorLibrary.h"
#include "BulletBase.generated.h"

USTRUCT()
struct FBulletTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = BulletStruct)
		FName Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = BulletStruct)
		int32 Damage;

	// パワーアップ2段階目時の追加ダメージ量
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = BulletStruct)
		int32 AddedDamageParamLv2;

	// パワーアップ3段階目時の追加ダメージ量
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = BulletStruct)
		int32 AddedDamageParamLv3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = BulletStruct)
		int32 ReloadBullet;

	// パワーアップ2段階目時のリロード倍数
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = BulletStruct)
		int32 ReloadBulletTimesLv2;

		// パワーアップ2段階目時のリロード倍数
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = BulletStruct)
		int32 ReloadBulletTimesLv3;

		
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = BulletStruct)
		float DeleteTime;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = BulletStruct)
		int32 Score;

	// ※パスについては、ディレクトリの始まりがContentからなので、その次のディレクトリから記入する.
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = BulletStruct)
		FString SoundPath;



};


/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ABulletBase : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	ABulletBase();

public:
	// Tick代わりのタイマーイベント
	UFUNCTION(BlueprintImplementableEvent)
	void OnEventByTimer();

	UFUNCTION(BlueprintCallable)
	void MovingBullet();

	UFUNCTION(BlueprintCallable)
	void AddHitBulletScore();

	// リロードと撃ちこみ点加算を一緒にやる
	UFUNCTION(BlueprintCallable)
	void ReloadAndAddScore(bool IsNotDestroyBullet);

// 実装検討中
//	UFUNCTION(BlueprintCallable)
//	void HitBulletByTarget(AActor* InHitActor);

	UFUNCTION(BlueprintPure)
	const int32 GetDamage()
	{
		return BulletTableRow.Damage;
	}

	UFUNCTION(BlueprintPure)
	const int32 GetScore()
	{
		return BulletTableRow.Score;
	}

	UFUNCTION(BlueprintPure)
	const int32 GetReloadBullet()
	{
		return BulletTableRow.ReloadBullet;
	}

	UFUNCTION(BlueprintPure)
	const float GetLivingTime() const
	{
		return LivingTime;
	}

	UFUNCTION(BlueprintPure)
	const float GetDeleteTime() const
	{
		return BulletTableRow.DeleteTime;
	}


	void SetDamageAndReloadPowerUp();

	UFUNCTION(BlueprintCallable)
	void SetPlayerAndPowerStatus(ATMMAPlayerBase* InPlayerBase);

	UFUNCTION(BlueprintPure)
	const bool GetIsHittedEnemyOrObject(AActor* HittedActor, UPrimitiveComponent* HittedPrimivateComponent) const
	{
		bool IsHitted = false;
		if (HittedActor->ActorHasTag("Enemy") || HittedPrimivateComponent->ComponentHasTag("CrushObjectCollision"))
		{
			IsHitted = true;
		}
		return IsHitted;
	}

	//　サウンド関連
	UFUNCTION(BlueprintCallable)
	void PlayShotSoundPlay();

	UFUNCTION(BlueprintCallable)
	void SetSoftShotSoundAndPlay();

	UFUNCTION(BlueprintCallable)
	void SetShotSoundBySoft();

	UFUNCTION(BlueprintPure)
	USoundBase* GetShotSound() const
	{
		return ShotSound;
	}

	// ゲームモード関連
	UFUNCTION(BlueprintCallable)
	void SetGameMode(ATestMyMakeActionGameModeBase* InGameMode);

	UFUNCTION(BlueprintPure)
	ATestMyMakeActionGameModeBase* GetMainGameMode() {
		return MainGameModeBase;
	}

	// ゲームステート関連
	UFUNCTION(BlueprintCallable)
	void SetMainGameState(ATMMAGameStateBase* InMainGameState);

	UFUNCTION(BlueprintPure)
	ATMMAGameStateBase* GetMainGameState() const
	{
		return MainGameState;
	}

	//プレイヤー関連
	UFUNCTION(BlueprintCallable)
	void SetPlayerBase(ATMMAPlayerBase* InPlayerBase);

	UFUNCTION(BlueprintPure)
	ATMMAPlayerBase* GetPlayerBase() {
		return PlayerBase;
	}


	UFUNCTION(BlueprintCallable, Category = "SetStatus")
	void SetBulletStatus(FName InRowName);

	// データアセット関連
	UFUNCTION(BlueprintCallable)
	void SetBulletStatusByAsset();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:


	float LivingTime = 0.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileMovement")
	class UProjectileMovementComponent* BulletProjectileMovement;

	// サウンド
	// TODO:: テーブルのデータから引っ張るようになったので廃止予定
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundBase> SoftShotSound;

	USoundBase* ShotSound;

	// ゲームモード
	TSubclassOf<ATestMyMakeActionGameModeBase> MainGameModeBaseClass;

	ATestMyMakeActionGameModeBase* MainGameModeBase;

	// ゲームステート
	ATMMAGameStateBase* MainGameState;

	// プレイヤー
	ATMMAPlayerBase* PlayerBase;

	// データ関連
	// TODO::データテーブルはデータアセットから取り込む予定になるので、もしかしたら廃止かも
	UPROPERTY(Category = "BulletDataTable", EditAnywhere, BlueprintReadWrite)
	class UDataTable* BulletDataTable;

	FBulletTableRow BulletTableRow;

	UPROPERTY(EditAnywhere)
	FName TableRowName;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTMMABulletDataAsset> SoftBulletDataAsset;

	UTMMABulletDataAsset* BulletDataAsset;
};

