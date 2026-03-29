// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIBase.h"
#include "Widget/TMMAItemList.h"
#include "ContinueWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UContinueWidget : public UGameUIBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitContinueTime();

	UFUNCTION(BlueprintCallable)
	void ReduceContinueTime();

	UFUNCTION(BlueprintCallable)
	void InitContinueCount();

	UFUNCTION(BlueprintCallable)
	void ReduceContinueCount();

	UFUNCTION(BlueprintPure)
	int GetContinueCount() {
		return ContinueCount;
	}

	UFUNCTION(BlueprintPure)
	float GetContinuleTime() {
		return ContinueTime;
	}

	UFUNCTION(BlueprintCallable)
	void SetItemList(UTMMAItemList* InItemList);

	UFUNCTION(BlueprintPure)
	UTMMAItemList* GetItemList() const {
		return ItemList;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContinueTime")
	float ContinueTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContinueCount")
	int ContinueCount = 10;

	UTMMAItemList* ItemList;

};
	