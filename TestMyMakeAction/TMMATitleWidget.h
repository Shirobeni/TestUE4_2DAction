// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIBase.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/TMMAItemList.h"
#include "Widget/TMMAItemButton.h"
#include "TMMARankingWidgetBase.h"
#include "TMMATitleWidget.generated.h"

/**
 * 
 */
UENUM()
enum class EViewMode : uint8
{
	Title UMETA(DisplayName = "Title"),
	Ranking UMETA(DisplayName = "Ranking"),
	Demo UMETA(DisplayName = "Demo")
};

UCLASS()
class TESTMYMAKEACTION_API UTMMATitleWidget : public UGameUIBase
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void DecideMenu();

	UFUNCTION(BlueprintCallable)
	void SetStartMenu(UTMMAItemList* InStartMenu);

	UFUNCTION(BlueprintPure)
	UTMMAItemList* GetStartMenu() {
		return StartMenu;
	}
	
	UFUNCTION(BlueprintCallable)
	void StartGame(int InItemIndex, APlayerController* InPlayerController);

	void InitViewCountAndComma();

	UFUNCTION(BlueprintCallable)
	void ReduceViewCount();

	UFUNCTION(BlueprintPure)
	const float GetViewConma() const
	{
		return ViewComma;
	}

	UFUNCTION(BlueprintPure)
	const int GetViewCount() const
	{
		return ViewCount;
	}

	UFUNCTION(BlueprintCallable)
	void SetIsLockViewCount(bool InIsLockViewCount);

	UFUNCTION(BlueprintPure)
	const bool GetIsLockViewCount() const
	{
		return IsLockViewCount;
	}

	UFUNCTION(BlueprintCallable)
	void SetIsView(bool InIsView);

	UFUNCTION(BlueprintPure)
	const bool GetIsView() const
	{
		return IsView;
	}

	UFUNCTION(BlueprintCallable)
	void ChangeViewCanvas(EViewMode InViewMode);

public:
	// ランキング用ウィジェット
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UTMMARankingWidgetBase* RankingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* TitleCanvas;

	// タイトルメニュー用パネル
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* StartMenuCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* RankingCanvas;

private:
	// スタートメニュー要ウィジェット
	UTMMAItemList* StartMenu = nullptr;

	bool IsStartMenu = false;

	int ViewCount = 5;

	float ViewComma = 10.0f;

	bool IsView = true;

	bool IsLockViewCount = false;

	EViewMode ViewMode = EViewMode::Title;

	// TODO::OptionMenuが出来たら追加.
};
