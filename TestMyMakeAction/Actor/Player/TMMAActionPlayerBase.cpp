
// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAActionPlayerBase.h"

void ATMMAActionPlayerBase::BeginPlay()
{
	SetPlayerMode(EPlayerMode::Action);
	Super::BeginPlay();
	SwordClass = SoftSwordClass.LoadSynchronous();
}

void ATMMAActionPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShotFunction();
}

void ATMMAActionPlayerBase::ShotFunction()
{
	if(IsAbleControll) {
		// ショットボタンを押しているか
		if(IsPussingShotButton) {
			if (IsAbleSwordAttack && !SwordAttackSwitch) {
				FTransform Transform = UKismetMathLibrary::MakeTransform(GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
				 GetWorld()->SpawnActor<AActor>(SwordClass, Transform);
				 SwordAttackSwitch = true;
				 // ソードの生成間隔をあけるための処理
				 ShotButtonPussingTime += 0.1f;
				 if (ShotButtonPussingTime >= MaxSwordWaitTime) {
					 ShotButtonPussingTime = 0.0f;
				 }
			}
			else {
				Shot(ShotAxisLeftRight, ShotAxisUpDown);
				if(IsMissileOfAction) {
					GetWorld()->GetTimerManager().SetTimer(Handle, this, &ATMMAActionPlayerBase::MissileShotFunc, 0.4f, false);
				}
			}
		}
		else {
			ShotButtonPussingTime = 0.0f;
		}
	}
}

void ATMMAActionPlayerBase::MissileShotFunc()
{
	ShotMissile(ShotAxisLeftRight);
}

void ATMMAActionPlayerBase::SetShotAxisLeftRight(float InShotAxisLeftRight)
{
	ShotAxisLeftRight = InShotAxisLeftRight;
}

void ATMMAActionPlayerBase::SetShotAxisUpDown(float InShotAxisUpDown)
{
	ShotAxisUpDown = InShotAxisUpDown;
}
