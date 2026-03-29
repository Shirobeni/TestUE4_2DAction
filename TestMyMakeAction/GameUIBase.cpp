// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUIBase.h"

void UGameUIBase::SetIsLockControll(bool InIsLockControll)
{
	IsLockControll = InIsLockControll;
}

//void UGameUIBase::BeginPlay()
//{
//	FTimerHandle TimerHandle;
//	GetWorldTimerManager().SetTimer(TimerHandle, this, &UGameUIBase::OnEventByTimer, 0.01f, true);
//	Super::BeginPlay();

//}
