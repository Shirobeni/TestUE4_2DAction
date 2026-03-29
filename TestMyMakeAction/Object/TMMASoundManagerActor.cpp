// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMASoundManagerActor.h"

void ATMMASoundManagerActor::SetSoundStructByDataAsset()
{
	// ソフト参照でデータアセット読み込み
	SoundManagerDataAsset = SoftSoundManagerDataAsset.LoadSynchronous();
	if (SoundManagerDataAsset != nullptr) {
		// null値でなければ構造体に格納していく
		for (FSoftSoundStruct SoftSoundStruct : SoundManagerDataAsset->SoftSoundStructList) {
			// SoundBaseに問題がないか確認.問題あったらスキップ.
			FSoundStructOld SoundStruct;
			SoundStruct.SoundBaseInstance = SoftSoundStruct.SoftSoundBase.LoadSynchronous();
			if (SoundStruct.SoundBaseInstance == nullptr) {
				continue;
			}
			// それ以降は問題ないとして追加.
			SoundStruct.SoundType = SoftSoundStruct.SoundType;
			SoundStruct.IndexOfType = SoftSoundStruct.IndexOfType;
			SoundStructList.Add(SoundStruct);
		}
	}
}

