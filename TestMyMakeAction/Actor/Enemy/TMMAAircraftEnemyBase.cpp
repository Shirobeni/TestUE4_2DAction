// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAAircraftEnemyBase.h"

void ATMMAAircraftEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Shot1TimerHandle;
	GetWorldTimerManager().SetTimer(Shot1TimerHandle, this, &ATMMAAircraftEnemyBase::ShotFunction1, 0.1f, true);
	FTimerHandle Shot2TimerHandle;
	GetWorldTimerManager().SetTimer(Shot2TimerHandle, this, &ATMMAAircraftEnemyBase::ShotFunction2, 0.4f, true);
}

void ATMMAAircraftEnemyBase::FunctionByTimerEvent()
{
	if (WasRecentlyRendered(0.0)) {
		if (GetInDistanceAtPlayerY(500.0f, -500.0f)) {
			FVector PlayerLocation = FVector(0.0f, 0.0f, 0.0f);
			UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
			FVector AimVector = GetAimToPlayer(GetActorLocation(), PlayerLocation);
			AddMovementInput(FVector(0.0f, AimVector.Y, 0.0f), 1.0);
		}
	}
}

void ATMMAAircraftEnemyBase::ShotFunction1()
{
	if (WasRecentlyRendered(0.0)) {
		if (GetInDistanceAtPlayerY(500.0f, -500.0f)) {
			FVector TargetVector = FVector(0.0f, 0.0f, 0.0f);
			UTMMAActorLibrary::GetPlayerLocation(TargetVector);
			AActor* SpawnActor;
			ShotEnemyBulletAimByIndex(FVector(1.0f, 1.0f, 1.0f), TargetVector, 0, FVector(3.0f, 3.0f, 3.0f), SpawnActor);
		}
	}
}

void ATMMAAircraftEnemyBase::ShotFunction2()
{
	if (WasRecentlyRendered(0.0)) {
		if (GetInDistanceAtPlayerY(500.0f, -500.0f)) {
			FVector TargetVector = FVector(0.0f, 0.0f, 0.0f);
			UTMMAActorLibrary::GetPlayerLocation(TargetVector);
			AActor* SpawnActor;
			ShotEnemyBulletAimByIndex(FVector(1.0f, 1.0f, 1.0f), TargetVector, 0, FVector(0.1f, 0.1f, 0.1f), SpawnActor);
		}
	}
}

