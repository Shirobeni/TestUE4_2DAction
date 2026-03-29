// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetMathLibrary.h"
#include "TestMyMakeAction/Actor/TMMAActorBase.h"
#include "TMMAGeneratorBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnDestroySpawnActor, AActor*);


USTRUCT()
struct FGeneratorTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GeneratorStruct)
		FName Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GeneratorStruct)
		AActor* SpawnClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GeneratorStruct)
		FVector SpawnVector;
};

UCLASS()
class TESTMYMAKEACTION_API ATMMAGeneratorBase : public ATMMAActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMMAGeneratorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void InitSingleStatus(TSubclassOf<AActor> InTargetActor, int InLimitCount);

	UFUNCTION(BlueprintCallable)
		void InitGenerateStatus(TArray<TSubclassOf<AActor>> InGenerateActorArray, int InGeneratorIndex);

	UFUNCTION(BlueprintCallable)
		void InitGeneratorActorByTable(TArray<FName> RowNameList);

	UFUNCTION(BlueprintCallable)
		void SpawnActor(FVector Location, FRotator Rotation, FVector Scale, bool UnlimitedFlag, AActor*& SActor);

	UFUNCTION(BlueprintCallable)
		void SetLimitCount(int InLimitCount);

	UFUNCTION(BlueprintPure)
		const int GetLimitCount() const
	{
		return LimitCount;
	}

	UFUNCTION(BlueprintCallable)
		void SetSpawnCount(int InSpawnCount);
	
	// スポーンカウントリセット用
	UFUNCTION(BlueprintCallable)
		void InitSpawnCount();

	UFUNCTION(BlueprintPure)
		const int GetSpawnCount() const
	{
		return SpawnCount;
	}

	UFUNCTION(BlueprintCallable)
		void SwitchGeneratorIndex(int InLimitIndex);

	UFUNCTION(BlueprintCallable)
		void SetGeneratorIndex(int InGeneratorIndex);

	UFUNCTION(BlueprintPure)
		const int GetGeneratorIndex() const {
		return GeneratorIndex;
	}

	UFUNCTION(BlueprintCallable)
		void SpawnGenerateActorArray(int ArrayIndex, FVector Location, FRotator Rotation, FVector Scale, AActor*& SActor);

	UFUNCTION(BlueprintCallable)
		void SetTriggerActor(AActor* InTriggerActor);

	UFUNCTION(BlueprintPure)
	AActor* GetTriggerActor() {
		return TriggerActor;
	}

	UFUNCTION(BlueprintCallable)
		void SetSpawnVector(FVector InSpawnVector);

	UFUNCTION(BlueprintPure)
		const FVector GetSpawnVector() const {
		return SpawnVector;
	}

	UFUNCTION(BlueprintCallable)
		void InitDestroyCount();

	UFUNCTION(BlueprintCallable)
		void AddDestroyCount();

	UFUNCTION(BlueprintPure)
		const int GetDestroyCount() const
	{
		return DestroyCount;
	}

	UFUNCTION(BlueprintCallable)
		void CountDownDestroy()
	{
		AddDestroyCount();
		if (DestroyCount >= LimitCount) {
			Destroy();
		}
	}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 生成したいアクタ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> TargetActor;

	// 何らかのトリガーとなるアクタ(指定したアクタの削除や、インデックスのスイッチに使う)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* TriggerActor;

	// ジェネレーターで生成した敵の撃破数
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int DestroyCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int LimitCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int SpawnCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> GenerateActorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int GeneratorIndex = 0;

	// 生成先用のベクトル
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector SpawnVector = FVector(0, 0, 0);

	UPROPERTY(Category = "GeneratorDataTable", EditAnywhere, BlueprintReadwrite)
		class UDataTable* DataTable;

	// 生成したアクタが破壊された時のデリゲート
	FOnDestroySpawnActor OnDestroySpawnActor;

};
