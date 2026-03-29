// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAActorBase.h"

// Sets default values
ATMMAActorBase::ATMMAActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMMAActorBase::BeginPlay()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATMMAActorBase::OnEventByTimer, 0.01f, true);
	Super::BeginPlay();
	
}

// Called every frame
void ATMMAActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

