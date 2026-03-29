// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/WidgetInterface.h"
#include "Components/CanvasPanel.h"
#include "GameUIBase.generated.h"


/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UGameUIBase : public UUserWidget, public IWidgetInterface
{
	GENERATED_BODY()

public:
//	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetIsLockControll(bool InIsLockControll);

	UFUNCTION(BlueprintPure)
	const bool GetIsLockControll() const
	{
		return IsLockControll;
	}

	// Tick代わりのイベント
	UFUNCTION(BlueprintImplementableEvent)
	void OnEventByTimer();

public:
	//操作等を受け付けない判定
	bool IsLockControll = false;

	
};
