// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "TMMARankingRowWidgetBase.h"
#include "TMMAGameInstanceBase.h"
#include "TMMARankingWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UTMMARankingWidgetBase : public UGameUIBase
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	void InitViewCountAndComma();

	UFUNCTION(BlueprintCallable)
	void ReduceViewCount();

	UFUNCTION(BlueprintPure)
	const int GetViewCount() const
	{
		return ViewCount;
	}

	UFUNCTION(BlueprintCallable)
	void SetRankingData(TArray<FRankingPlayerStatus> RankingPlayerStatuses);

	UFUNCTION(BlueprintCallable)
	void SetIsView(bool InIsView);

	UFUNCTION(BlueprintPure)
	const bool GetIsView() const
	{
		return IsView;
	}


public:
	int ViewCount = 7;

	float ViewComma = 10.0f;

	bool IsView = true;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UVerticalBox* RankingVerticalBox = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTMMARankingRowWidgetBase> RankingRowWidget = nullptr;
};
