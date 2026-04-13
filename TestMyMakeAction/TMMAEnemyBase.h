// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Math/Rotator.h"
#include "DrawDebugHelpers.h"
#include "TMMAEnemyBulletBase.h"
#include "TestMyMakeActionGameModeBase.h"
#include "Library/TMMAActorLibrary.h"
#include "GameState/TMMAGameStateBase.h"
#include "TMMAEnemyActorBulletInterface.h"
#include "DataAsset/Enemy/TMMAEnemyDataAsset.h"
#include "TMMAEnemyBase.generated.h"

#define ADD_STAGETIME_FOR_DEFEATED_BOSS 60.0f;

USTRUCT()
struct FEnemyTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = EnemyStruct)
		FName Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = EnemyStruct)
		int Hp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = EnemyStruct)
		int Score;
};


UCLASS()
class TESTMYMAKEACTION_API ATMMAEnemyBase : public ACharacter, public IEnemyActorAndBulletInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATMMAEnemyBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 現在の形態パターンを取得
	UFUNCTION(BlueprintPure)
	const int GetPatternTransform() const {
		return PatternTransform;
	}

	UFUNCTION(BlueprintPure)
		const int32 GetEnemyHp() const {
		return Hp;
	}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Destroyをタイマー経由で呼び出したいための関数(試験投入)
	void DestroyFunction();

	// 指定秒数ごとに実行するためのカスタムイベント(Tick代わりに使用する)
	UFUNCTION(BlueprintImplementableEvent)
	void OnEventByTimer();

	// ↑用の関数(オーバーライド可)
	virtual void FunctionByTimerEvent();

	// ショット処理のDelay実行用
	void ShotDelayFunction(float* InShotFloat, float InShotDelayFloat, TFunction<void()> ShotFuncCallBack);

	// ダメージ用インターフェースのオーバーライド
	virtual void Damage_Implementation(int InDamage, bool IsTimes) override;

	// BeginPlay時の処理をひとまとめ
	UFUNCTION(BlueprintCallable)
	void InitStateByBeginPlay();

	UFUNCTION(BlueprintCallable)
	void SetEnemyHp(int InHp);

	// ダメージまたは破壊時の処理
	UFUNCTION(BlueprintCallable)
	void DamageOrDestroyEnemy(int InDamageParam, bool IsTimes);

	// 爆風生成
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnDestroyExplotion(FVector InVector);
	virtual void SpawnDestroyExplotion_Implementation(FVector InVector);

	// ステージボス撃破の小爆発
	void SpawnBossExplosionSmall();


	UFUNCTION(BlueprintCallable)
	void SetEnemyScore(int InScore);

	UFUNCTION(BlueprintPure)
	const int32 GetEnenyScore() const
	{
		return Score;
	}

	UFUNCTION(BlueprintPure)
	const int32 GetDiffScore() const
	{
		return Score / 5;
	}

	UFUNCTION(BlueprintCallable, Category = "SetEnemyStatus")
	bool setEnemyStatus(FName SetRowName, FEnemyTableRow& EnemyParam);

	// データアセットからの読み込み
	void SetEnemyStatusByAsset();

	UFUNCTION(BlueprintCallable)
	void MoveEnemy(FVector AddVector);

	// 最大生態時間を設定
	UFUNCTION(BlueprintCallable)
		void SetMaxLivingTime(float InMaxLivingTime);

	UFUNCTION(BlueprintCallable)
		void AddLivingTime(float AddTimeParam);

	UFUNCTION(BlueprintPure)
	const float GetLivingTime() const
	{
		return LivingTime;
	}

	// ボス敵のみ。各パターンステータスを初期状態に
	UFUNCTION(BlueprintCallable)
	void InitPatternStatus();

	// パターンカウントを進めつつ、パターン等を変化
	UFUNCTION(BlueprintCallable)
	void CountingPatternCount(int ChangeMod, int EndCount);

	//パターンタイプを設定
	UFUNCTION(BlueprintCallable)
	void SetPatternType(int InPatterrnType);


	// パターンタイプを取得
	UFUNCTION(BlueprintPure)
	const int GetPatternType() const {
		return PatternType;
	}

	UFUNCTION(BlueprintCallable)
		void LoopPatternType(int LimitType);

	// パターンカウントを設定
	UFUNCTION(BlueprintCallable)
	void SetPatternCount(int InPatternCount);

	//パターンカウントを取得
	UFUNCTION(BlueprintPure)
	const int GetPatternCount() const {
		return PatternCount;
	}

	// 形態変化
	UFUNCTION(BlueprintCallable)
	void SetPatternTransForm(int InPatternTransform);

	// 形態移行時のウェイトフラグ
	UFUNCTION(BlueprintCallable)
	void SetTransformWaitFlag(bool InTransformWaitFlag);

	UFUNCTION(BlueprintPure)
		const bool GetTransformWaitFlag() const
	{
		return TransformWaitFlag;
	}

	// タイマー関連の設定.(※現状は試用段階)
//	template<typename T>
//	void SetTimerFromFunction(FTimerHandle InHandle, T* TargetObj, void(T::*Func)(), float Rate);

	// ソフト参照のアクタクラス配列リストを、サブクラスのアクタクラス配列リストに変換.
	UFUNCTION(BlueprintCallable)
	void SetActorClassArraySoftToSubClass();

	// ソフト参照の弾クラス配列リストを、サブクラスの弾クラス配列リストに変換.
	UFUNCTION(BlueprintCallable)
	void SetShotClassArraySoftToSubclass();

	// 弾の間隔調整フラグ
	UFUNCTION(BlueprintPure)
	bool GetShotLag(int OnFlagParam);

	// 自機狙いの弾を出す。
	// 通常版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletAim(FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, AActor*& SpawnShot);

	// ソフト参照版
	UFUNCTION(BlueprintCallable, meta = (InScale = "InScale", sample = "FVector(1,1,1)"))
	void ShotEnemyBulletAimBySoft(FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, AActor*& SpawnShot);

	// クラス配列のインデックス指定
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletAimByIndex(FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, AActor*& SpawnShot);

	// ベクトル指定
	// 通常版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletAimForVerctor(FVector SetVector, FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, AActor*& SpawnShot);

	// ソフト参照版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletAimForVertorBySoft(FVector SetVector, FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, AActor*& SpawnShot);

	// クラス配列のインデックス指定
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletAimForVerctorByIndex(FVector SetVector, FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, AActor*& SpawnShot);

	// 自機狙いのTransformを取得する
	UFUNCTION(BlueprintPure, meta = (InScale = "InScale", sample = "FVector(1,1,1)"))
	void GetEnemyBulletAim(FVector SetVector, FVector TargetVector, FVector InScale, FTransform& GetTransform);

	// 自機狙いで多方向弾
	// 通常
	UFUNCTION(BlueprintCallable, meta = (InScale = "InScale", sample = "FVector(1,1,1)"))
	void ShotEnemyWayBulletAim(FVector SetVector, FVector TargetVector, FVector InScale, int CombineIndex, float CombineAngle, TSubclassOf<AActor> BulletActor);

	// ↑のソフト参照版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyWayBulletAimBySoft(FVector SetVector, FVector TargetVector, FVector InScale, int CombineIndex, float CombineAngle, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor);

	// クラス配列のインデックス指定
	UFUNCTION(BlueprintCallable)
	void ShotEnemyWayBulletAimByIndex(FVector SetVector, FVector TargetVector, FVector InScale, int CombineIndex, float CombineAngle, int BulletIndex);


	// X軸をもとに弾を出す
	// 通常版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVector(FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, AActor*& SpawnShot);

	// ↑のソフト参照版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorBySoft(FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, AActor*& SpawnShot);

	// クラス配列のインデックス指定
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorByIndex(FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, AActor*& SpawnShot);

	// ShotEnemyBulletXVector()のベクトル指定版
	// 通常版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorForVector(FVector SetVector, FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, AActor*& SpawnShot);

	// ↑のソフト参照版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorForVectorBySoft(FVector SetVector, FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, AActor*& SpawnShot);

	// クラス配列のインデックス指定
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorForVectorByIndex(FVector SetVector, FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, AActor*& SpawnShot);

	// Combine補正あり
	// 通常版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorByCombine(FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, FRotator AddRotate, AActor*& SpawnShot);

	// ↑のソフト参照版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorByCombineBySoft(FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, FRotator AddRotate, AActor*& SpawnShot);

	// クラス配列のインデックス指定
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorByCombineByIndex(FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, FRotator AddRotate, AActor*& SpawnShot);


	// ShotEnemyBulletXVector()のベクトル指定+角度指定版
	// 通常版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorForVectorByCombine(FVector SetVector, FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, FRotator AddRotate, AActor*& SpawnShot);

	// ↑のソフト参照版
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorForVectorByCombineBySoft(FVector SetVector, FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, FRotator AddRotate, AActor*& SpawnShot);

	// クラス配列のインデックス指定
	UFUNCTION(BlueprintCallable)
	void ShotEnemyBulletXVectorForVectorByCombineByIndex(FVector SetVector, FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, FRotator AddRotate, AActor*& SpawnShot);

	// ショットクラス配列より、指定したインデックスの値を取得.
	UFUNCTION(BlueprintPure)
	TSubclassOf<ATMMAEnemyBulletBase> GetBulletClassByIndex(int Index) const
	{
		if (ShotEnemyBulletList[Index] != nullptr) {
			return ShotEnemyBulletList[Index];
		}
		else {
			return nullptr;
		}
	}

	// アクタクラス配列より、指定したインデックスの値を取得
	UFUNCTION(BlueprintPure)
	TSubclassOf<AActor> GetSpawnActorClassByIndex(int Index) const
	{
		if (SpawnActorClassList[Index] != nullptr) {
			return SpawnActorClassList[Index];
		}
		else {
			return nullptr;
		}
	}

	UFUNCTION(BlueprintCallable)
	void EnemyDamage(int InDamage);

	// 被弾・撃破音およびパーティクルを設定(ソフト参照)
	UFUNCTION(BlueprintCallable)
	void SetDamageAndDefeatedSoundAndParticleBySoft(TSoftObjectPtr<USoundBase> InSoftDamageSound, TSoftObjectPtr<class USoundBase> InSoftDefeatSound, TSoftObjectPtr<class USoundBase> InSoftDeathrattleSound, TSoftObjectPtr<class USoundBase> InSoftDefeatBossSmallSound, TSoftObjectPtr<class USoundBase> InSoftDefeatBossSemiSound, TSoftObjectPtr<class UParticleSystem> InDamageParticle, TSoftObjectPtr<class UParticleSystem> InDefeatParticle, TSoftObjectPtr<class UParticleSystem> InDefeatBossSmallParticle);

	// 被弾音をセットする
	UFUNCTION(BlueprintCallable)
	void SetDamageSound(USoundBase* InSound);

	// ↑のソフト参照版
	UFUNCTION(BlueprintCallable)
	void SetDamageSoundBySoft(TSoftObjectPtr<USoundBase> InSoftDamageSound);

	UFUNCTION(BlueprintPure)
	USoundBase* GetDamageSound() const {
		return DamageSound;
	}

	// 雑魚用撃破音声・爆風を設定
	UFUNCTION(BlueprintCallable)
	void SetDefeatForEnemy(TSoftObjectPtr<class USoundBase> InSoftDefeatSound, TSoftObjectPtr<class UParticleSystem> InDamageParticle, TSoftObjectPtr<class UParticleSystem> InDefeateParticle);

	// ボス用撃破音声・爆風を設定
	UFUNCTION(BlueprintCallable)
	void SetDefeatForBoss(TSoftObjectPtr<class USoundBase> InSoftDefeatSound, TSoftObjectPtr<class USoundBase> InSoftDeathrattleSound, TSoftObjectPtr<class USoundBase> InSoftDefeatBossSmallSound, TSoftObjectPtr<class USoundBase> InSoftDefeatBossSemiSound, TSoftObjectPtr<class UParticleSystem> InDamageParticle, TSoftObjectPtr<class UParticleSystem> InDefeateParticle, TSoftObjectPtr<class UParticleSystem> InDefeatBossSmallParticle);

	// ソフト参照のSE及びパーティクルをオブジェクト化
	void SetSoftToObjSeAndParticle();

	// ソフト参照のランダム爆風をクラス化
	UFUNCTION(BlueprintCallable)
	void SetRandomDefeatedFireSoftToSubclass();

	// ランダムの爆風生成
	UFUNCTION(BlueprintCallable)
	void SpawnRandomDefeatedFire(FTransform InTransform);

	// 自機と敵の距離を取得
	UFUNCTION(BlueprintPure)
		const FVector GetDistanceAtPlayer();

	// 自機と敵の各軸が範囲内かのチェック
	// X軸
	UFUNCTION(BlueprintPure)
	const bool GetInDistanceAtPlayerX(float PlusDistance, float MinusDistance);

	// Y軸
	UFUNCTION(BlueprintPure)
	const bool GetInDistanceAtPlayerY(float PlusDistance, float MinusDistance);

	// Z軸
	UFUNCTION(BlueprintPure)
	const bool GetInDistanceAtPlayerZ(float PlusDistance, float MinusDistance);

	// 初期位置の取得
	UFUNCTION(BlueprintPure)
	const FVector GetStartEnemyPosition() const
	{
		return StartEnemyPosition;
	}

	// ゲームモードをハード化して設定
	// TODO::ゲームモード参照のため、廃止の可能性あり.
	UFUNCTION(BlueprintCallable)
	void SetAndSyncroGameMode(TSoftObjectPtr<class ATestMyMakeActionGameModeBase> InGameModeObject);

	UFUNCTION(BlueprintCallable)
	void SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode);

	UFUNCTION(BlueprintPure)
	ATestMyMakeActionGameModeBase* GetMainGameMode() const
	{
		return GameMode;
	}

	/* ゲームステート関連 */
	UFUNCTION(BlueprintCallable)
	void SetMainGameState(ATMMAGameStateBase* InMainGameState);

	UFUNCTION(BlueprintPure)
	ATMMAGameStateBase* GetMainGameState() const
	{
		return MainGameState;
	}

	// 撃破された時のパーティクルとSEを生成
	UFUNCTION(BlueprintCallable)
	void SpawnDefeatedPerticleAndSe(UParticleSystem* InParticle, USoundBase* InSe, FVector InVector);

	// 撃破時のパーティクルとSEをランダムの種類で生成
	UFUNCTION(BlueprintCallable)
		void SpawnRandomDefeatedParticleAndSe(UParticleSystem* InParticle, USoundBase* InSe, FVector InVector);

	// 撃破時の加算タイムをセット
	UFUNCTION(BlueprintCallable)
	void SetAddTime(float InAddTime);

	// 撃破時の加算タイムを取得
	UFUNCTION(BlueprintPure)
	const float GetAddTime() const
	{
		return AddTime;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool LineTraceByTargetToPlayer(FVector StartVector, FVector TargetVector, float TraceDistance, ECollisionChannel TraceChannel, FHitResult& HitResult);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		const FVector GetAimToPlayer(FVector EnemyVector, FVector PlayerVector);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<ATMMAEnemyBulletBase> GetEnemyBulletBySubclass(int Index);

	void SetIsDefeated(bool InIsDefeated);

	UFUNCTION(BlueprintPure)
	const bool GetIsDefeated() const
	{
		return IsDefeated;
	}

	// 生成した敵弾のリストへ追加.(ボス撃破後の削除等に使う.)
	UFUNCTION(BlueprintCallable)
	void AddSpawnActorList(AActor* SpawnActor);

	// 画面上の敵弾削除.
	UFUNCTION(BlueprintCallable)
	void DestroyAllSpawnActor();

	// データアセットの取得
	UFUNCTION(BlueprintPure)
	UTMMAEnemyDataAsset* GetEnemyDataAsset() const
	{
		return EnemyDataAsset;
	}

	// スケルタルメッシュ用マテリアルの取得.
	UFUNCTION(BlueprintPure)
	TArray<UMaterial*> GetSkeltalMaterialArray() const
	{
		return SkeltalMaterialArray;
	}

	// 子スタティックメッシュリストの取得
	UFUNCTION(BlueprintPure)
	TArray<UStaticMesh*> GetChildStaticMeshArray() const
	{
		return ChildStaticMeshList;
	}

	// 子スケルタルメッシュリストの取得
	UFUNCTION(BlueprintPure)
	TArray<USkeletalMesh*> GetChildSkeletaleMeshArray() const
	{
		return ChildSkeltalMeshList;
	}

public:
	// 形態変更用パーティクル
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UParticleSystem> TransformParticle;

	// 形態変更用サウンド
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundBase> TransformSound;


protected:
	// Called when the game starts or when spawned
	int32 Hp;

	int32 Score;

	// 敵攻撃のパターン
	int32 PatternType;

	// パターンのカウント
	int32 PatternCount;

	// 生態時間
	float LivingTime = 0;

	// 最大生態時間
		float MaxLivingTime = 0;

	// 敵の形態
	int32 PatternTransform = 1;

	// 形態変更時のウェイトフラグ(ちゃんと正常なタイミング、位置で次の形態の攻撃を行いたいため)
	bool TransformWaitFlag = false;

	// 撃破フラグ
	bool IsDefeated = false;

	USoundBase* DamageSound;

	// 撃破音
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class USoundBase> SoftDefeatSound;

	USoundBase* DefeatSoundObj;

	// ボス撃破時の小爆発音
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class USoundBase> SoftDefeatBossSmallSound;

	USoundBase* DefeatBossSmallSoundObj;

	// ボス撃破時の中爆発音
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class USoundBase> SoftDefeatBossSemiSound;

	USoundBase* DefeatBossSemiSoundObj;


	// 断末魔(主にボスに使用する)
	TSoftObjectPtr<class USoundBase> SoftDeathrattleSound;

	USoundBase* DeathrattleSoundObj;



	// ダメージを受けたときに使用するパーティクル
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UParticleSystem> DamageParticle;

	UParticleSystem* DamageParticleObj;

	// 破壊時に使用するパーティクル
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UParticleSystem> DefeatParticle;

	UParticleSystem* DefeatParticleObj;


	// ステージボス破壊時に使用する小爆発パーティクル
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UParticleSystem> DefeatBossSmallParticle;

	UParticleSystem* DefeatBossSmallParticleObj;

	// ランダムで表示される爆風
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> RandomDefeatedFire;

	// テストで↑のソフト参照版
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<class AActor> SoftRandomDefeatedFire;

	/* ゲームモード関連 */
	// ゲームモード
	ATestMyMakeActionGameModeBase* GameMode;

	// 上のソフトバン
	TSoftObjectPtr<class ATestMyMakeActionGameModeBase> GameModeObject;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftClassPtr<AActor>> SpawnActorSoftList;

	TArray<TSubclassOf<AActor>> SpawnActorClassList;

	TArray<AActor*> SpawnActorList;

	// 生成敵弾リスト
	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftClassPtr<ATMMAEnemyBulletBase>> SoftShotEnemyBulletList;

	TArray<TSubclassOf<ATMMAEnemyBulletBase>> ShotEnemyBulletList;

	FEnemyTableRow EnemyTableRow;

	UPROPERTY(Category = "EnemyDataTable", EditAnywhere, BlueprintReadwrite)
	class UDataTable* DataTable;

	// 撃破時に加算されるタイム(ボスのみ適用)
	float AddTime;

	// 敵の初期位置
	FVector StartEnemyPosition;

	// タイマーイベントの実行フレーム
	UPROPERTY(EditAnywhere)
	float TimerEventFlame = 0.016f;

	// パターン用カウント(通常ショットに使用する)
	int PatternCountChangeMod = 0;

	int PatternCountEndCount = 0;


	// データアセット
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTMMAEnemyDataAsset> SoftEnemyDataAsset;

	UTMMAEnemyDataAsset* EnemyDataAsset;

	USkeletalMesh* ParentSkeltalMesh;

	TArray<UStaticMesh*> ChildStaticMeshList;

	TArray<USkeletalMesh*> ChildSkeltalMeshList;

	TArray<UMaterial*> SkeltalMaterialArray;

	// ゲームステート関連
	ATMMAGameStateBase* MainGameState;

private:
	FTimerHandle TimerEventHandle;

};
