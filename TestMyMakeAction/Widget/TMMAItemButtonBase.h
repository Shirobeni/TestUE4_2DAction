// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/GameUIBase.h"
#include "TMMAItemButtonBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UTMMAItemButtonBase : public UGameUIBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetItemIndex(int InIndex);

	UFUNCTION(BlueprintPure)
	const int GetItemIndex() const {
		return ItemIndex;

	}

public:
	int ItemIndex;
};
