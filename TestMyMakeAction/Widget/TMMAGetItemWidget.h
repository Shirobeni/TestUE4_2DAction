// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/GameUIBase.h"
#include "Components/TextBlock.h"
#include "TMMAGetItemWidget.generated.h"

/**
 * 
 */
/*
UENUM(BlueprintType)
enum class EGetItemType : unit8
{
	PowerUp UMETA(DisplayName = "PowerUp"),
	Rapid UMETA(DisplayName = "Rapid"),
	Homing UMETA(DisplayName = "Homing"),
	Fire UMETA(DisplayName = "Fire"),
	Grenade UMETA(DisplayName = "Grenade"),
	Laser UMETA(DisplayName = "Laser"),
	Burst UMETA(DisplayName = "Burst"),
};
*/

UCLASS()
class TESTMYMAKEACTION_API UTMMAGetItemWidget : public UGameUIBase
{
	GENERATED_BODY()
	
public:
	void SetGetItemText(FString InTextString);

	void SetGetItemTextColor(FLinearColor InItemTextBaseColor);
	
	UFUNCTION(BlueprintCallable)
	void AddViewCountAndChangeTextColor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GetItemText;


private:
	FLinearColor ItemTextBaseColor = FLinearColor(1.0f, 0.1f, 0.0f, 1.0f);

	int ViewCount = 0;

//	EGetItemType GetItemType = EGetItemType::PowerUp;


};
