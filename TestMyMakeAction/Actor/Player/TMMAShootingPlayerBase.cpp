// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAShootingPlayerBase.h"

void ATMMAShootingPlayerBase::BeginPlay()
{
	SetPlayerMode(EPlayerMode::Shooting);
	Super::BeginPlay();
}

void ATMMAShootingPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShotFunction();
	MissileShotOfFunc();
}

void ATMMAShootingPlayerBase::SetIsPussingMissileButton(bool InIsPussingMissileButton)
{
	IsPussingMissileButton = InIsPussingMissileButton;
}

void ATMMAShootingPlayerBase::ShotFunction()
{
	if (!IsAbleControll) return; // 操作不能の場合は何もしない
	if (!IsPussingShotButton) return; // ショットボタンが押されていない
	Shot(0.0f, 0.0f);
}

void ATMMAShootingPlayerBase::MissileShotOfFunc()
{
	if (IsPussingMissileButton) {
		MissileFloat += 0.1f;
		if (MissileFloat >= MissileDelecateFloat) {
			ShotMissile(1.0f);
			MissileFloat = 0.0f;
		}
	}
	else {
		MissileFloat = 0.0f;
	}
}