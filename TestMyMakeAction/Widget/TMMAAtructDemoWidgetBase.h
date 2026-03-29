// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/GameUIBase.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TestMyMakeAction/TMMAGameInstanceBase.h"
#include "TestMyMakeAction/TMMARankingWidgetBase.h"
#include "TestMyMakeAction/TMMAMaingameWidgetBase.h"
#include "TestMyMakeAction/Object/TMMACustomWorldSettings.h"
#include "TMMAAtructDemoWidgetBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAttructViewMode : uint8
{
	Title UMETA(DisplayName = "Title"),
	DemoPlay UMETA(DisplayName = "Demo"),
	Ranking UMETA(DisplayName = "Ranking"),
	ReadyStart UMETA(DisplaytName = "ReadyStart")
};

UCLASS()
class TESTMYMAKEACTION_API UTMMAAtructDemoWidgetBase : public UGameUIBase
{
	GENERATED_BODY()

protected:
	UTMMAAtructDemoWidgetBase();
	
	bool Initialize() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void ChangeWidgetCanvasMode(ELevelMode InLevelMode);

	UFUNCTION()
	FText SetCreditCountText();

	UFUNCTION()
	FText SetCoinCountText();

public:
	// ランキング用ウィジェット
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTMMARankingWidgetBase* RankingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* RankingCanvas;

	// デモプレイ用ウィジェット
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTMMAMaingameWidgetBase* MainGameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* DemoPlayCanvas;

	// タイトル画面
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* TitleCanvas;

	// クレジット投入後のスタート準備画面
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* ReadyStartCanvas;

	// 投入コイン数
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CreditCountText;

	// 投入クレジット数
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CoinCountText;

private:
	// 表示モード
	EAttructViewMode AttructViewMode = EAttructViewMode::Title;

	// ゲームインスタンス
	UTMMAGameInstanceBase* GameInstanceBase;
};
