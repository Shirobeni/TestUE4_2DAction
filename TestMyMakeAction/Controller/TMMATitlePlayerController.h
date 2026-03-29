// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestMyMakeAction/TMMATitleWidget.h"
#include "TMMAPlayerController.h"
#include "TMMATitlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMATitlePlayerController : public ATMMAPlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void CreateTitleWidgetBySoftClass();

	UFUNCTION(BlueprintPure)
	// タイトル画面用ウィジェットの取得
	UTMMATitleWidget* GetTitleWidget() const
	{
		return TitleWidget;
	}

public:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UTMMATitleWidget> SoftTitleWidgetClass;

private:
	UTMMATitleWidget* TitleWidget;
};
