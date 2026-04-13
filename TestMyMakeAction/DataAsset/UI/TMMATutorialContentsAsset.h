// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TestMyMakeAction/TMMAGameInstanceBase.h"
#include "TMMATutorialContentsAsset.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTextStruct 
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere)
	int32 index;

	UPROPERTY(EditAnywhere)
		FString TutorialContent;
};

UCLASS()
class TESTMYMAKEACTION_API UTMMATutorialContentsAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FTextStruct> JapaneseTextStructList;
};
