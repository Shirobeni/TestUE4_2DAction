// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMMAOtherActor.h"
#include "Widget/TMMAGetItemWidget.h"
#include "TMMAGetItemActor.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGetItemType : uint8
{
	PowerUp UMETA(DisplayName = "PowerUp"),
	Rapid UMETA(DisplayName = "Rapid"),
	Homing UMETA(DisplayName = "Homing"),
	Fire UMETA(DisplayName = "Fire"),
	Grenade UMETA(DisplayName = "Grenade"),
	Laser UMETA(DisplayName = "Laser"),
	Burst UMETA(DisplayName = "Burst"),
	Life UMETA(DisplayName = "Life"),
};



UCLASS()
class TESTMYMAKEACTION_API ATMMAGetItemActor : public ATMMAOtherActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetGetItemWidgetBySoft();

	UFUNCTION(BlueprintPure)
	UTMMAGetItemWidget* GetItemGetWidget() const
	{
		return GetItemWidget;
	}

	void SetItemType(EGetItemType InGetItemType);

	UFUNCTION(BlueprintCallable)
	void SetItemTypeAndText(EGetItemType InGetItemType, int ItemLevel);

	EGetItemType GetGetItemType() const
	{
		return GetItemType;
	}


public:
	// アイテム取得用ウィジェット
	// ソフト
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UTMMAGetItemWidget> GetItemWidgetSoftClass;

private:
	UTMMAGetItemWidget* GetItemWidget;

	EGetItemType GetItemType = EGetItemType::PowerUp;

};
