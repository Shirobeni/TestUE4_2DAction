// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAEyesEnemyBase.h"

void ATMMAEyesEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	if (UTMMAEyesEnemyDataAsset* CastedEyesEnemyDataAsset= Cast<UTMMAEyesEnemyDataAsset>(EnemyDataAsset)){
		EyesEnemyDataAsset = CastedEyesEnemyDataAsset;
		switch (EyesEnemyDataAsset->CategoryType) {
			default:
				break;
			case EEyesEnemyCategotyType::Laser:
				ShotDelayFloat = 0.05f;
				break;
			case EEyesEnemyCategotyType::Shot:
				ShotDelayFloat = 0.2f;
				if (!UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) return;
				SetHomingToPlayer();
				ProjectileMovementComp->MaxSpeed = 300.0f;
				break;
		}
	}
}

void ATMMAEyesEnemyBase::FunctionByTimerEvent()
{
	Super::FunctionByTimerEvent();
	if (!WasRecentlyRendered(0.0f)) return;
	switch (EyesEnemyDataAsset->CategoryType)
	{
		default:
			break;
		case EEyesEnemyCategotyType::Laser:
			ActionTypeLaser();
			break;
		case EEyesEnemyCategotyType::Shot:
			ActionTypeShot();
			break;
	}
}

void ATMMAEyesEnemyBase::SetProjectileMovementComp(UProjectileMovementComponent* InProjectileMovementComp)
{
	ProjectileMovementComp = InProjectileMovementComp;
}

void ATMMAEyesEnemyBase::ActionTypeLaser()
{
	if (GetDistanceAtPlayer().Y <= -200.0f && GetDistanceAtPlayer().Y >= 200.0f) return;
	if (ShotAbleCount >= 70) {
		ShotAbleCount = 0;
	}
	else {
		ShotAbleCount++;
		if (ShotAbleCount >= 40) {
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				Shot();
			});
		}
	}
}

void ATMMAEyesEnemyBase::ActionTypeShot()
{
	if (GetDistanceAtPlayer().Z <= 200.0f && GetDistanceAtPlayer().Z >= -200.0f)
	{
		if (!UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) return;
		SetHomingToPlayer();
		ShotAbleCount++;
		if (ShotAbleCount >= 60) {
			ShotAbleCount = 0;
		}
		else {
			if (ShotAbleCount >= 30) {
				ProjectileMovementComp->MaxSpeed = 0.1f;
				ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
					Shot();
				});
			}
			else {
				ProjectileMovementComp->MaxSpeed = 800.0f;
			}
			ProjectileMovementComp->bIsHomingProjectile = true;
		}
	}
	else {
		ProjectileMovementComp->MaxSpeed = 0.1f;
	}
}

void ATMMAEyesEnemyBase::Shot()
{
	FVector StartVector = FVector(0.0f, 0.0f, 0.0f);
	FVector ScaleVector = FVector(0.3f, 0.3, 1.0f); // デフォルトはレーザーの大きさ想定
	if (EyesEnemyDataAsset->CategoryType == EEyesEnemyCategotyType::Shot) {
		ScaleVector = FVector(0.7, 0.7, 0.3);
	}
	FVector PlayerVector;
	UTMMAActorLibrary::GetPlayerLocation(PlayerVector);
	AActor* SpawnShot;
	ShotEnemyBulletAimByIndex(StartVector, PlayerVector, 0, ScaleVector, SpawnShot);
	if (!SpawnShot) return;
	if (EyesEnemyDataAsset->CategoryType == EEyesEnemyCategotyType::Laser) {
		SpawnShot->AddActorWorldRotation(FRotator(90.0f, 0.0f, 0.0f));
	}
}

void ATMMAEyesEnemyBase::SetHomingToPlayer()
{
	USceneComponent* PlayerComponent = NewObject<USceneComponent>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	ProjectileMovementComp->HomingTargetComponent = PlayerComponent;
}