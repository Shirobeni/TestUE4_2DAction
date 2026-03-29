// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIBase.h"
#include "Components/Image.h"
#include "TMMAPlayerLeftWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UTMMAPlayerLeftWidgetBase : public UGameUIBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* PlayerLeftImage = nullptr;
};
