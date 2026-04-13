// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMASemiBoss2Base.h"

void ATMMASemiBoss2Base::BeginPlay()
{
	Super::BeginPlay();
	SetAddTime(30.0f);
}

void ATMMASemiBoss2Base::FunctionByTimerEvent()
{
	Super::FunctionByTimerEvent();
	if (!GameMode->GetIsBossBattle() || IsDefeated) return;
	UTMMAActorLibrary::MoveActorToTarget(this, UGameplayStatics::GetPlayerPawn(GetWorld(), 0), 0.3f);
	BulletCount++;
	if (BulletCount >= MaxBulletCount) {
		BulletCount = 0;
	}
	if (BulletCount >= AbleBulletCount) {
		ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
			ShotRapidEnemyBullet();
		});
	}
	ShotDelayFunction(&MissileFloat, MissileDelayFloat, [this]() {
		ShotMissile();
	});
	InstantAnimation();
}

void ATMMASemiBoss2Base::SetMissileCannonComponent(USkeletalMeshComponent* InMissileCannonComponent)
{
	// 必ずBP側でBeginPlayで読み込んでおくこと！
	MissileCannonComponent = InMissileCannonComponent;
}

void ATMMASemiBoss2Base::SetCannonComponent(USkeletalMeshComponent* InCannonComponent)
{
	// 必ずBP側でBeginPlayで読み込んでおくこと！
	CannonComponent = InCannonComponent;
}

void ATMMASemiBoss2Base::ShotRapidEnemyBullet()
{
	FVector CannonVector = CannonComponent->GetComponentLocation();
	FVector Location = GetActorLocation();
	CannonVector.Z += 50;
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector ScaleVector = FVector(0.3f, 0.3f, 0.3f);
	AActor* SpawnShot;
	ShotEnemyBulletAimForVerctorByIndex(BulletSetVec, CannonVector, PlayerLocation, 0, ScaleVector, SpawnShot);
}

void ATMMASemiBoss2Base::ShotMissile()
{
	FVector MissileCannonVector = MissileCannonComponent->GetComponentLocation();
//	MissileCannonVector.Y -= 100.0f;
//	MissileCannonVector.Z += 200.0f;
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector ScaleVector = FVector(1.0f, 1.0f, 1.0f);
	AActor* SpawnShot;
	ShotEnemyBulletAimForVerctorByIndex(BulletSetVec, MissileCannonVector, PlayerLocation, 1, ScaleVector, SpawnShot);
}

void ATMMASemiBoss2Base::InstantAnimation()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	FRotator LookRotator = UKismetMathLibrary::FindLookAtRotation(
		GetActorLocation(),
		PlayerLocation
	);
	LookRotator.Roll = 0.0f;
	LookRotator.Pitch = 0.0f;
	MissileCannonComponent->SetWorldRotation(LookRotator);
	CannonComponent->SetWorldRotation(LookRotator);
}