// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/Actor/TMMAActorBase.h"
#include "TestMyMakeAction/DataAsset/Actor/TMMASoundManagerDataAsset.h"
#include "TMMASoundManagerActor.generated.h"

/**
 * 
 */
 
USTRUCT(BlueprintType)
struct FSoundStructOld
{
	GENERATED_USTRUCT_BODY()

	USoundBase* SoundBaseInstance;

	EGameSoundType SoundType = EGameSoundType::Stage;

	int IndexOfType; // サウンドタイプごとのインデックス値.
};

 
UCLASS()
class TESTMYMAKEACTION_API ATMMASoundManagerActor : public ATMMAActorBase
{
	GENERATED_BODY()
	
public:
	void SetSoundStructByDataAsset();
	
	FSoundStructOld GetSoundStruct(EGameSoundType InSoundType, int InIndexOfType)
	{
		FSoundStructOld ReturnSoundStruct;
		for (FSoundStructOld SoundStruct : SoundStructList) {
			if (InSoundType == SoundStruct.SoundType && InIndexOfType == SoundStruct.IndexOfType) {
				// サウンドタイプとインデックス値の一致で取得.
				ReturnSoundStruct = SoundStruct;
			}
		}
		return ReturnSoundStruct;
	}

public:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTMMASoundManagerDataAsset> SoftSoundManagerDataAsset;

private:
	UTMMASoundManagerDataAsset* SoundManagerDataAsset;

	TArray<FSoundStructOld> SoundStructList;
};
