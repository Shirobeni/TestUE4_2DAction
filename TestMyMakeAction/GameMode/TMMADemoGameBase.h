// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestMyMakeAction/Actor/OtherPawn/TMMAAtructDemoControllPawn.h"
#include "TMMADemoGameBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAtructType : uint8
{
	Title UMETA(DisplayName = "Title"),
	DemoPlay UMETA(DisplayName = "DemoPlay"),
	Ranking UMETA(DisplayName = "Ranking"),
	ReadyCredit UMETA(DisplayName = "ReadyCredit")
};

UCLASS()
class TESTMYMAKEACTION_API ATMMADemoGameBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	void LoadDemoLevel();

	void OpenNextDemoLevel();

public:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<ATMMAAtructDemoControllPawn> SoftAtractPawnClass;
	
private:
	ATMMAAtructDemoControllPawn* AtractPawn;

	EAtructType AtructType = EAtructType::Title;
	
	float ViewTime = 0.0f;
	
	float MaxViewTime = 0.0f;
	
	// 各シーンごとの最大表示秒数
	TMap<EAtructType, float> MaxViewTimeList = {
		{EAtructType::Title, 5.0f},
		{EAtructType::DemoPlay, 10.0f},
		{EAtructType::Ranking, 10.0f},
	};

	// クレジット投入状態か
	bool IsCreditInserted = false;

	// 次のレベル表示用フラグ
	bool IsOpenLevelDoOnce = false;
};
