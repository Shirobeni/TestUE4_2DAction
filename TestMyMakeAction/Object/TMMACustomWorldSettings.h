// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "TestMyMakeAction/GameState/TMMAGameStateBase.h"
#include "TestMyMakeAction/DataAsset/Actor/TMMASoundManagerDataAsset.h"
#include "TMMACustomWorldSettings.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ELevelMode : uint8
{
	Stage UMETA(DisplayName = "Stage"), // ステージとして扱う
	Menu UMETA(DisplayName = "Menu"), // メニュー.
	Title UMETA(DisplayName = "Title"), // タイトル
	DemoPlay UMETA(DisplayName = "DemoPlay"), // デモプレイ
	Ranking UMETA(DisplayName = "Ranking"), // ランキング
	ReadyStart UMETA(DisplayName = "ReadyStart"), // クレジット投入後のスタート準備
	Test UMETA(DisplayName="Test") //テスト用
};

UCLASS()
class TESTMYMAKEACTION_API ATMMACustomWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	// レベル形式
	UPROPERTY(EditAnywhere)
	ELevelMode LevelMode = ELevelMode::Stage;

	// 現在ステージ
	UPROPERTY(EditAnywhere)
	ECurrentStageEnum CurrentStage = ECurrentStageEnum::Stage1;

	
	UPROPERTY(EditAnywhere)
	UTMMASoundManagerDataAsset* SoundDataAsset;
};
