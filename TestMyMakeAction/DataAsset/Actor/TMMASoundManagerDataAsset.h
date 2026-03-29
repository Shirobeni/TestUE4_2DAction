// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "Engine/DataAsset.h"
#include "TMMASoundManagerDataAsset.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameSoundType : uint8
{
	Stage UMETA(DisplayName="Stage"),
	Boss UMETA(DisplayName="Boss"),
	Demo UMETA(DisplayName="Demo"),
	NameEntry UMETA(DisplayName="NameEntry")
};

USTRUCT(BlueprintType)
struct FSoftSoundStruct
{
	GENERATED_USTRUCT_BODY()
	// ƒTƒEƒ“ƒh
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundBase> SoftSoundBase;

	UPROPERTY(EditAnywhere)
	EGameSoundType SoundType = EGameSoundType::Stage;

	UPROPERTY(EditAnywhere)
	int IndexOfType;
};

UCLASS()
class TESTMYMAKEACTION_API UTMMASoundManagerDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FSoftSoundStruct> SoftSoundStructList;
};
