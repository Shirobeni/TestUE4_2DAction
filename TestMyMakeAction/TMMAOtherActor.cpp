// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAOtherActor.h"

// Sets default values
ATMMAOtherActor::ATMMAOtherActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMMAOtherActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMMAOtherActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMMAOtherActor::AddLivingTime(float InLivingTime)
{
	LivingTime += InLivingTime;
}

void ATMMAOtherActor::SetMaxLivingTime(float InMaxLivingTime)
{
	MaxLivingTime = InMaxLivingTime;
}

