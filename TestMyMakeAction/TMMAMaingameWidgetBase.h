// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameState/TMMAGameStateBase.h"
#include "TMMAGameInstanceBase.h"
#include "TMMAPlayerLeftWidgetBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widget/TMMADirectionWidget.h"
#include "TMMAMaingameWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UTMMAMaingameWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetLeftIcon(TSubclassOf<UTMMAPlayerLeftWidgetBase> InPlayerLeftIcon);

	UFUNCTION(BlueprintCallable)
	void UpdateLeft(int InViewCount);

	UFUNCTION(BlueprintCallable)
	void UpdateBurstCount(int InBurstCount);

	UFUNCTION(BlueprintCallable)
	void SetStageAndStageTitleText(int CurrentStageNum, EBuildMode InBuildMode);

	UFUNCTION(BlueprintCallable)
	void AddStageTitleViewTime();

	UFUNCTION(BlueprintPure)
	UTMMADirectionWidget* GetDirectionWidget()
	{
		return DirectionWidget;
	}

	UFUNCTION(BlueprintCallable)
	void SetDirectionWidgetByIsLeftSide(bool InIsDirectionLeftSide);


private:
	UFUNCTION()
	FText SetPlayer1ScoreText();

	UFUNCTION()
	FText SetTimeText();

	UFUNCTION()
	FText SetHighScoreText();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Player1ScoreText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TimeText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HighScoreText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* P1LifeVitalText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* P1BurstCountText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* LeftIconList = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* StageTitlePanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StageText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StageSubTitleText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTMMADirectionWidget* DirectionWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTMMAPlayerLeftWidgetBase> PlayerLeftIcon = nullptr;

	float StageTitleViewTime = 0.0f;

	float MaxStageTitleViewTime = 5.0f;

	bool StageTitleViewTimeStopFlag = false;

private:
	ATMMAGameStateBase* MainGameState;
};
