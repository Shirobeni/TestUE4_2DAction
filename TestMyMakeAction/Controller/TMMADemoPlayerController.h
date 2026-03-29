// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMMAPlayerController.h"
#include "TestMyMakeAction/Widget/TMMAAtructDemoWidgetBase.h"
#include "TMMADemoPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMADemoPlayerController : public ATMMAPlayerController
{
	GENERATED_BODY()

public:
	void CreateAtructDemoWidget();

	UTMMAAtructDemoWidgetBase* GetAtructDemoWidget() const
	{
		return AtructDemoWidget;
	}

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void InsertCoin();

public:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UTMMAAtructDemoWidgetBase> SoftAtructDemoWidgetClass;

private:
	UTMMAAtructDemoWidgetBase* AtructDemoWidget;

};
