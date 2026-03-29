// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss3Base.h"

void ATMMABoss3Base::BeginPlay()
{
	Super::BeginPlay();
	PatternCountChangeMod = 30;
	PatternCountEndCount = 240;
	LanceTimeCount = 0;
}

void ATMMABoss3Base::FunctionByTimerEvent()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	if (FVector::Dist(GetActorLocation(), PlayerLocation) > 200.0f) return;
	if (!WasRecentlyRendered(0.0)) return;
	if ((!GameMode) || (!GameMode->GetIsBossBattle())) return;
	if (!IsDefeated) {
		CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
		BossAttack();
		MoveLanceRotate();
		if(Hp < 4000 && TransformChangeOnceFlag == false){
			InitPatternStatus();
			PatternTransform = 2;
			TransformChangeOnceFlag = true;
		}
	}
}

void ATMMABoss3Base::BossAttack()
{
	if (IsDefeated) return;
	switch (PatternTransform) {
		default:
			break;
		case 1:
			switch (PatternType) {
				default:
					break;
				case 0:
					if (PatternCount >= 10) {
						LanceAngleShot();
					}
					break;
				case 1:
					LanceAttack();
					break;
				case 2:
					if (PatternCount >= 10) {
						ShotDelayFloat = 0.2f;
						ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
							SpreadShot();
						});
//						GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss3Base::SpreadShot, 0.2f, false);
					}
					break;
			}
			break;
		case 2:
			switch (PatternType) {
				default:
					break;
				case 0:
					ShotDelayFloat = 0.2f;
					ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
						SpredShotByPt2();
						});
//					GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss3Base::SpredShotByPt2, 0.2f, false);
					break;
				case 1:
					LanceComponent->AddWorldOffset(FVector(0.0f, -10.0f, 0.0f));
					break;
				case 2:
					LanceComponent->AddWorldOffset(FVector(0.0f, 10.0f, 0.0f));
					break;
			}
			break;
	}
}

void ATMMABoss3Base::SetBaseSceneComponent(USceneComponent* InBaseSceneComponent)
{
	BaseSceneComponent = InBaseSceneComponent;
}

void ATMMABoss3Base::SetLanceComponent(USceneComponent* InLanceComponent)
{
	LanceComponent = InLanceComponent;
}

void ATMMABoss3Base:: SetSceneLanceComp(USceneComponent* InSceneLanceComp)
{
	SceneLanceComp = InSceneLanceComp;
}

void ATMMABoss3Base:: MoveLanceRotate()
{
	if(PatternTransform == 2 && PatternType != 0) {
		LanceComponent->AddWorldRotation(FRotator(30.0f, 0.0f, 0.0f));
	} else {
		FVector PlayerLocation;
		UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
		FVector LanceLocation = LanceComponent->GetComponentLocation();
		FRotator LanceRotator = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, LanceLocation);
		LanceRotator.Pitch -= 85.0;
		LanceComponent->SetWorldRotation(LanceRotator);
	}
}

void ATMMABoss3Base::LanceAngleShot()
{
	InVector = FVector(0.0f, 1.0f, 0.0f);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector SceneLanceLocation = SceneLanceComp->GetComponentLocation(); 
	float AddPitchRotate = (PatternCount * 10) * 30.0f;
	AActor* SpawnShot;
	ShotEnemyBulletXVectorForVectorByCombineByIndex(BulletSetVec, SceneLanceLocation, InVector, 0, FVector(0.7f, 0.7f, 0.5f), FRotator(0.0f, AddPitchRotate, 0.0f), SpawnShot);
	LanceComponent->SetWorldLocation(SceneLanceComp->GetComponentLocation());
}

void ATMMABoss3Base::LanceAttack()
{
	LanceTimeCount++;
	if (LanceTimeCount > 40) {
		LanceTimeCount = 0;
	}
	else {
		FVector AddLanceVect = FVector(0.0f, -30.0f, 0.0);
		if (LanceTimeCount > 10) {
			AddLanceVect.Y = 10.0f;
		}
		LanceComponent->AddWorldOffset(AddLanceVect);
	}
}

void ATMMABoss3Base::SpreadShot()
{
	InVector = FVector(0.0f, -1.0f, -1.0f);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector LanceSceneVec = SceneLanceComp->GetComponentLocation();
	float AddPitchRotate = (PatternCount * 10) * 30.0f;
	AActor* SpawnShot;
	ShotEnemyBulletXVectorForVectorByCombineByIndex(BulletSetVec, LanceSceneVec, InVector, 1, FVector(0.7f, 0.7f, 0.5f), FRotator(0.0f, AddPitchRotate, 0.0f), SpawnShot);
}

void ATMMABoss3Base::SpredShotByPt2()
{
	InVector = FVector(0.0f, -3.0f, -1.0f);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector LanceSceneVec = SceneLanceComp->GetComponentLocation();
	float AddPitchRotate = UKismetMathLibrary::RandomFloatInRange(0.0f, 120.0f);
	AActor* SpawnShot;
	ShotEnemyBulletXVectorForVectorByCombineByIndex(BulletSetVec, LanceSceneVec, InVector, 1, FVector(0.7f, 0.7f, 0.5f), FRotator(0.0f, AddPitchRotate, 0.0f), SpawnShot);
	if (!SpawnShot) return;
	if (ATMMAEnemyBulletBase* CastedSpawnShot = Cast<ATMMAEnemyBulletBase>(SpawnShot)) {
		CastedSpawnShot->GetProjectileMovement()->Velocity *= UKismetMathLibrary::RandomFloatInRange(10.f, 4.0f);
	}
}