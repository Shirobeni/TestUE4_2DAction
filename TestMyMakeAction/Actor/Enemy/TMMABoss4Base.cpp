// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss4Base.h"

void ATMMABoss4Base::BeginPlay()
{
	Super::BeginPlay();
	PatternCountChangeMod = 80;
	PatternCountEndCount = 480;
}


void ATMMABoss4Base::FunctionByTimerEvent()
{
	if (!GameMode->GetIsBossBattle()) return;
	if (!WasRecentlyRendered(0.0f)) return;
	if (IsDefeated) return;
	CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
	BossAttack();
	if (Hp < 4000 && (!TransformDoOnceFlag)){
		TransformDoOnceFlag = true;
		InitPatternStatus();
		PatternTransform = 2;
		DestroyAllSpawnActor();
	}
	
}

void ATMMABoss4Base::BossAttack()
{
	switch(PatternTransform){
		default:
			break;
		case 1:
			switch(PatternType) {
				default:
					break;
				case 0:
					JumpCount = 0;
					SpawnLaserAndRotate();
					break;
				case 1:
					SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
					ShotDelayFloat = 0.05f;
					ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
						SpawnDestroyableShot();
					});
//					GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss4Base::SpawnDestroyableShot, 0.05, false);
					break;
				case 2:
					JumpAttack();
					ShotDelayFloat = 0.6f;
					ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
						SpawnHomingShot();
					});
//					GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss4Base::SpawnHomingShot, 0.6, false);
					break;
			}
			break;
		case 2:
			switch (PatternType) {
				default:
				case 2:
					JumpAttack();
					break;
				case 0:
					JumpCount = 0;
					ShotDelayFloat = 0.05f;
					ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
						SpawnDestroyableShot();
					});
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss4Base::SpawnDestroyableShot, 0.05, false);
					break;
			}

	}
}

void ATMMABoss4Base::SpawnLaserAndRotate()
{
	FVector StartVector = FVector(0.0f, 0.0f, 0.0f);
	InVector = FVector(-1.0f, 0.0f, 0.0f);
	FVector ScaleVector = FVector(0.5f, 0.5f, 0.5f);
	float AddYawParam = ((PatternCount / 10.0) - LimitPatternCount) * 60;
	AActor* SpawnLaser;
	ShotEnemyBulletXVectorByCombineByIndex(StartVector, InVector, 0, ScaleVector, FRotator(0.0f, AddYawParam, 0.0f), SpawnLaser);
	AddActorLocalRotation(FRotator(0.0f, 5.0, 0.0f));
	if(!SpawnLaser) return;
	SpawnLaser->SetActorScale3D(ScaleVector);
}

void ATMMABoss4Base::SpawnDestroyableShot()
{
	InVector = FVector(0.0f, -3.0f, 0.0f);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector EnemyLocation = GetActorLocation();
	EnemyLocation.Y -= 150.0f;
	float AddPitchParam = UKismetMathLibrary::RandomFloat() * (-30.0);
	AActor* DestroyableShot;
	ShotEnemyBulletXVectorForVectorByCombineByIndex(BulletSetVec, EnemyLocation, InVector, 1, FVector(1.0f, 1.0f, 1.0f), FRotator(0.0f, AddPitchParam, 0.0f), DestroyableShot);
}

void ATMMABoss4Base::SpawnHomingShot()
{
	InVector = FVector(0.0, -1.0, 0.0);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector EnemyLocation = GetActorLocation();
	EnemyLocation.Y -= 150.0f;
	EnemyLocation.Z += 50.0f;
	AActor* HomingShot;
	ShotEnemyBulletXVectorForVectorByIndex(BulletSetVec, EnemyLocation, InVector, 2, FVector(1.0f, 1.0f, 1.0f), HomingShot);
}

void ATMMABoss4Base::JumpAttack()
{
	switch (PatternTransform) {
		default:
			break;
		case 1:
			JumpCount++;
			if (JumpCount <= 60) {
				MoveEnemy(FVector(0.0f, -10.0f, 0.0f));
				Jump();
				IsAttackable = true;
			}
			else {
				MoveEnemy(FVector(0.0f, 30.0f, 0.0f));
				IsAttackable = false;
			}
			break;
		case 2:
			if (JumpCount >= 250) {
				// 上昇弾を設置された場所から発射
				for (ATMMAEnemyBulletBase* RiseSeedBullet : RiseSeedBulletList) {
					TSubclassOf<ATMMAEnemyBulletBase> RiseBulletClass = ShotEnemyBulletList[4];
					FVector SeedBulletLocation = RiseSeedBullet->GetActorLocation();
					FTransform Transform = UKismetMathLibrary::MakeTransform(SeedBulletLocation, FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f));
					GetWorld()->SpawnActor<ATMMAEnemyBulletBase>(RiseBulletClass, Transform);
				}
				RiseSeedBulletList.Empty();
			}
			else {
				JumpCount++;
				if (JumpCount >= 190) {
					IsAttackable = false;
					MoveEnemy(FVector(0.0f, 15.0f, 0.0));
				} else {
					Jump();
					MoveEnemy(FVector(0.0f, -5.0f, 0.0));
					if (bWasJumping) {
						// ジャンプで着地した所に上昇する弾の種を置く.
						TSubclassOf<ATMMAEnemyBulletBase> RiseSeedBulletClass = ShotEnemyBulletList[3];
						FVector EnemyLocation = GetActorLocation();
						EnemyLocation.Z -= -150.0f;
						FTransform Transform = UKismetMathLibrary::MakeTransform(EnemyLocation, FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f));
						ATMMAEnemyBulletBase* RiseSeedBullet =  GetWorld()->SpawnActor<ATMMAEnemyBulletBase>(RiseSeedBulletClass, Transform);
						if (!RiseSeedBullet) {
							RiseSeedBulletList.Add(RiseSeedBullet);
						}
					}
				}
			}
	}
}