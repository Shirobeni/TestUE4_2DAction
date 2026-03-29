// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Library/TMMAActorLibrary.h"
#include "Engine/DataTable.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Library/TMMAProjectileUtil.h"
#include "TMMAEnemyActorBulletInterface.h"
#include "TestMyMakeAction/Actor/TMMAActorBase.h"
#include "TMMAEnemyBulletBase.generated.h"

USTRUCT()
struct FEnemyBulletTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = EnemyBulletStruct)
	FName Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = EnemyBulletStruct)
	int DamageParam;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = EnemyBulletStruct)
	float LimitTime;

	// ※パスについては、ディレクトリの始まりがContentからなので、その次のディレクトリから記入する.
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = EnemyBulletStruct)
	FString SoundPath;
};

UCLASS()
class TESTMYMAKEACTION_API ATMMAEnemyBulletBase : public ATMMAActorBase,  public IEnemyActorAndBulletInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMMAEnemyBulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	UProjectileMovementComponent* GetProjectileMovement() const {
		return  BulletProjectileMovement;
	}

protected:
	UFUNCTION(BlueprintCallable)
	void MovingBullet(float AddTime, float LiveTime);

	UFUNCTION(BlueprintCallable, Category = "SetEnemyBulletStatus")
	bool SetEnemyBulletStatus(FName SetRowName, FEnemyBulletTableRow& EnemyBulletParam);

	UFUNCTION(BlueprintCallable)
	void SetBulletLivingTime(float InLivingTime);

	UFUNCTION(BlueprintCallable)
	void SetBulletLimitTime(float InLimitTime);

	UFUNCTION(BlueprintCallable)
	void SetBulletSpeed(float VectorMul);

	UFUNCTION(BlueprintCallable)
	void SetBulletSpeedOnRank(int Rank);

	UFUNCTION(BlueprintPure)
	const float GetLivingTime() const {
		return LivingTime;
	}

	UFUNCTION(BlueprintCallable)
	void SetBulletLife(int InLife);

	UFUNCTION(BlueprintPure)
	const int GetBulletLife() const {
		return BulletLife;
	}

	UFUNCTION(BlueprintCallable)
	void AddBulletLife(int AddLife);

	// サウンド関連
	UFUNCTION(BlueprintCallable)
	void PlayShotSound();

protected:
	UPROPERTY(Category = "EnemyBulletDataTable", EditAnywhere, BlueprintReadwrite)
	class UDataTable* DataTable;

	float Damage;

	float LivingTime;

	float LimitTime = 2.0;

	UPROPERTY(BlueprintReadOnly)
	int BulletLife = 0;

	FEnemyBulletTableRow EnemuyBulletTableRow;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* BulletProjectileMovement;
	
	USoundBase* ShotSound;
};
