// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAObjectBase.h"

// Sets default values
ATMMAObjectBase::ATMMAObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMMAObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMMAObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMMAObjectBase::SetSwitchFlag(bool InSwitchFlag)
{
	SwitchFlag = InSwitchFlag;
}

void ATMMAObjectBase::InitMoveTime()
{
	MoveTime = 0.0;
}

void ATMMAObjectBase::AddMoveTime(float InMoveTime) {
	if (LimitMoveTime) {
		MoveTime += InMoveTime;
	}
}

void ATMMAObjectBase::SetLimitMoveTime(float InLimitMoveTime)
{
	LimitMoveTime = InLimitMoveTime;
}
