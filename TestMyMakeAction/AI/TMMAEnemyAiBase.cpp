// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAEnemyAiBase.h"

void ATMMAEnemyAiBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATMMAEnemyAiBase::SetControllEnemy(ATMMAEnemyBase* InControllEnemy)
{
	ControlleEnemy = InControllEnemy;
}

void ATMMAEnemyAiBase::SetIsArrivedPoint(bool InIsArrivedPoint)
{
	IsArrivedPoint = InIsArrivedPoint;
}

void ATMMAEnemyAiBase::SetIsAbleMove(bool InIsAbleMove)
{
	IsAbleMove = InIsAbleMove;
}

void ATMMAEnemyAiBase::SetIsUnlimitedDistance(bool InIsUnlimitedDistance)
{
	IsUnlimitedDistance = InIsUnlimitedDistance;
}