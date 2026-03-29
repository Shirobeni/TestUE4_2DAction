// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/GameUIBase.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "TMMADirectionWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EDirectionType : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down")
};


UCLASS()
class TESTMYMAKEACTION_API UTMMADirectionWidget : public UGameUIBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ChangeColorText();

	UFUNCTION(BlueprintCallable)
	void AddViewCountAndViewCheck();

	UFUNCTION(BlueprintCallable)
	void SetIsView(bool InIsView);

	UFUNCTION(BlueprintPure)
	const bool GetIsView() const
	{
		return IsView;
	}

	UFUNCTION(BlueprintCallable)
	void SetDirectionType(EDirectionType InDirectionType);

	UFUNCTION(BlueprintCallable)
	void SetDirectionTypeAndText(EDirectionType InDirectionType);


	UFUNCTION(BlueprintPure)
	EDirectionType GetDirectionType() const 
	{
		return DirectionType;
	}

	void SetIsLeftSide(bool InIsLeftSide);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* L_DirectionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* R_DirectionText;


private:
	bool IsView = false;

	int ViewCount = 0;

	int LimitViewCount = 100;

	EDirectionType DirectionType = EDirectionType::Left;

	bool IsLeftSide = false;

};
