// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAPlayerController.h"

void ATMMAPlayerController::BeginPlay() {
	Super::BeginPlay();
}


void ATMMAPlayerController::SetControllPlayer(ATMMAPlayerBase* InControllPlayer)
{
	ControllPlayer = InControllPlayer;
}

void ATMMAPlayerController::SetControllPawn(APawn* InControllPawn)
{
	ControllPawn = InControllPawn;
}