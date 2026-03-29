// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TestMyMakeAction/TMMAEnemyBulletBase.h"
#include "TMMAEnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UTMMAEnemyDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	

public:
	// 敵キャラクター名
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName EnemyName;

	// 体力
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Hp;

	// 撃破時のスコア
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Score;
	
	// ダメージSE
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundBase> SoftDamageSound;

	// 撃破SE(※爆発音)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundBase> SoftDefeatedSound;

	// 撃破ボイス(ほぼボス用)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundBase> SoftDeathrattleSound;

	// ボス用撃破SE(小爆発)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundBase> SoftDefeatBossSmallSound;

	// ボス用撃破SE(中爆発)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USoundBase> SoftDefeatBossSemiSound;

	// ダメージ用パーティクル 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UParticleSystem> SoftDamageParticle;

	// 撃破用パーティクル
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UParticleSystem> SoftDefeateParticle;

	// ボス用撃破パーティクル
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UParticleSystem> SoftDefeatBossSmallParticle;

	// 敵キャラなどの生成オブジェクトクラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftClassPtr<AActor>> SpawnActorSoftClassList;

	// 敵弾クラスリスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftClassPtr<ATMMAEnemyBulletBase>> SoftShotEnemyBulletClassList;

	// スケルタルメッシュ(※使用する場合)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> SoftSkeltalMesh;

	// マテリアル配列(※スケルタルメッシュ用に使用する)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UMaterial>> SoftSkeltalMaterialList;

	// スタティックメッシュ配列(メッシュに子付けして使用する想定)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UStaticMesh>> SoftStaticMeshList;

	// スケルタルメッシュ配列(メッシュに子付けして使用する想定)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<TSoftObjectPtr<USkeletalMesh>> SoftChildSkeletalMeshList;
};
