// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TestMyMakeAction/Library/TMMAUnrealLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "TMMAActorLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UTMMAActorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// プレイヤーキャラの位置ベクトル取得
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static void GetPlayerLocation(FVector& PlayerLocation);

	// プレイヤーキャラのTransformを取得
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static void GetPlayerTransform(FTransform& PlayerTransform);

	// 特定アクタに加算分のベクトルを取得
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void GetActorLocationForAdd(AActor* InActor, FVector AddVector, FVector& ComponentLocation);

	// 特定コンポーネントに加算分のベクトルを取得
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void GetComponentLocationForAdd(USceneComponent* InComponent, FVector AddVector, FVector& ActorLocation);

	// 指定アクタへ狙うTransform作成用
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static void GetAimTransform(FVector SetVector, AActor* StartActor, AActor* TargetActor, FVector ScaleVector, FTransform& GetTransform);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static void GetAimTransformAngle(FVector SetVector, AActor* StartActor, AActor* TargetActor, FVector ScaleVector, int CombineIndex, float Angle, FTransform& GetTransform);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static void GetAimTransformForVector(FVector SetVector, FVector StartVector, FVector TargetVector, FVector ScaleVector, FTransform& GetTransform);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static void GetRoundTransformForVector(FVector SetVector, FVector StartVector, FVector TargetVector, FVector ScaleVector, FRotator InB_Rotator, FTransform& GetTransform);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static void GetAimTransformComponent(FVector SetVector, USceneComponent* StartComponent, USceneComponent* TargetCompoonent, FVector ScaleVector, FTransform& GetTransform);

	// Xベクトル軸Transform作成.
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static void GetXVectorTransform(FVector SetVector, FVector StartVector, FVector TargetVector, FVector ScaleVector, FTransform& GetTransform);
		
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void GetXVectorTransformByCombine(FVector SetVector, FVector StartVector, FVector TargetVector, FVector ScaleVector, FRotator AddRotate, FTransform& GetTransform);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static bool GetDistanceIn(float Float1, float Float2, float PlusDistance, float MinusDistance);

		// 互いのアクタの各軸の距離内かの判定を求める.
	UFUNCTION(BlueprintCallable, BlueprintPure)
		static bool GetIsInDistanceX(AActor* Actor1, AActor* Actor2, float PlusDistance, float MinusDistance);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static bool GetIsInDistanceY(AActor* Actor1, AActor* Actor2, float PlusDistance, float MinusDistance);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		static bool GetIsInDistanceZ(AActor* Actor1, AActor* Actor2, float PlusDistance, float MinusDistance);


	// タイム計算用(float計算何でも使えるので名前変えてもいいのかも)
	UFUNCTION(BlueprintCallable)
		static void AddMigityTime(float SetTime, float AddTime, float LimitTime, float& NowTime);

	// SEとパーティクル同時生成
	UFUNCTION(BlueprintCallable)
		static void SpawnSeAndParticle(AActor* InActor, UParticleSystem* Particle, USoundBase* Se, FVector InVector, FVector InScale);

	// ↑をソフト参照で行う
	UFUNCTION(BlueprintCallable)
		static void SpawnSeAndParticleBySoft(AActor* InActor, TSoftObjectPtr<UParticleSystem> SoftParticle, TSoftObjectPtr<USoundBase> SoftSe, FVector InVector, FVector InScale);

	// アクタのベクトル移動
	UFUNCTION(BlueprintCallable)
		static void AddActorVector(AActor* InActor, FVector AddVector);

	// コンポーネントのベクトル移動
	UFUNCTION(BlueprintCallable)
	static void AddComponentVector(USceneComponent* InComponent, FVector AddVector);

	// 浮動小数点数分加算してベクトル移動
	UFUNCTION(BlueprintCallable)
		static void AddActorVectorWithFloat(AActor* InActor, FVector AddVector, float AddFloat);

	UFUNCTION(BlueprintCallable)
		static void SetRotatorForEase(AActor* EasedActor, AActor* TargetActor, float InAlpha, bool InIsShortestPath, TEnumAsByte<EEasingFunc::Type> InEasingType);

//	UFUNCTION(BlueprintCallable, BlueprintPure)
//		static bool LineTraceByTargetToPlayer(FVector StartVector, FVector TargetVector, float TraceDistance, ECollisionChannel TraceChannel);

	UFUNCTION(BlueprintCallable)
	static void MoveActorToTarget(AActor* MoveActor, AActor* TargetActor, float MoveVelocity);

	UFUNCTION(BlueprintCallable)
	static void GetIsInRangeVector(AActor* TargetActor1, AActor* TargetActor2, float DiffRange_X, float DiffRange_Y, float DiffRange_Z, bool& IsInRangeX, bool& IsInRangeY, bool& IsInRangeZ);

	// タグによる地形接触判定
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetIsHitBrushByTag(AActor* UsedActor, FName TagName);
};
