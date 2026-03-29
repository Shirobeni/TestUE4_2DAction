// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Library/TMMAActorLibrary.h"
#include "TMMAEnemyActorBulletInterface.h"
#include "TestMyMakeActionGameModeBase.h"
#include "Particles/ParticleSystemComponent.h"  
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "TestMyMakeAction/Actor/TMMAActorBase.h"
#include "TMMADestroiedObjectBase.generated.h"

#define DEFAULT_PARTICLE_FLOAT_SIZE 1.0f;

USTRUCT()
struct FClashObjectTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = ObjectStruct)
		FName Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = ObjectStruct)
		int Hp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = ObjectStruct)
		int Score;

	UPROPERTY(Category = "Particle", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<UParticleSystem> SoftParticleData;

	UPROPERTY(Category = "Se", EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<USoundBase> SoftSe;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = ObjectStruct)
		FVector ParticleScale;

};

UCLASS()
class TESTMYMAKEACTION_API ATMMADestroiedObjectBase : public ATMMAActorBase, public IEnemyActorAndBulletInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMMADestroiedObjectBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetHp(int InHp);

	UFUNCTION(BlueprintPure)
	const int GetHp() const
	{
		return Hp;
	}

	UFUNCTION(BlueprintCallable)
	void SetScore(int InScore);

	UFUNCTION(BlueprintCallable)
	const int GetScore() const
	{
		return Score;
	}

	UFUNCTION(BlueprintCallable)
	bool setObjectStatus(FName SetRowName, FClashObjectTableRow& EnemyParam);

	UFUNCTION(BlueprintCallable)
	void SetParticle(UParticleSystem* InParticle);

	UFUNCTION(BlueprintCallable)
	UParticleSystem* GetParticle() const
	{
		return Particle;
	}

	UFUNCTION(BlueprintCallable)
	void SetDestroySe(USoundBase* InDestroySe);

	UFUNCTION(BlueprintPure)
	USoundBase* GetDestroySe() const
	{
		return DestroySe;
	}

	void SetParticleScale(FVector InParticleScale);

	UFUNCTION(BlueprintCallable)
	void DamageObject(int DamageParam, bool IsTimes);

	UFUNCTION(BlueprintCallable)
	void SpawnDestroyParticleAndSe();

	UFUNCTION(BlueprintCallable)
	bool ActiveExplotionParticle();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	int Hp;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	class UDataTable* DataTable;

	int Score;

	ATestMyMakeActionGameModeBase* GameMode;

	UPROPERTY(Category = "ClashObjectTableRow", EditAnywhere, BlueprintReadWrite)
	FClashObjectTableRow ClashObjectTableRow;

//	UPROPERTY(Category = "SceneComponent", VisibleDefaultsOnly, BlueprintReadWrite)
//	class USceneComponent* SceneComponent;

	UPROPERTY(Category = "Particle", EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* Particle;
	
	UPROPERTY(Category = "ParticleSystemComponent", VisibleAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* ParticleSystemComponent;

	FVector ParticleScale;

	USoundBase* DestroySe;
};
