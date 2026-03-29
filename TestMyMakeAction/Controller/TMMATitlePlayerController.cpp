// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMATitlePlayerController.h"

void ATMMATitlePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATMMATitlePlayerController::CreateTitleWidgetBySoftClass()
{
	TSubclassOf<UTMMATitleWidget> TitleWidgetClass = SoftTitleWidgetClass.LoadSynchronous();
	if (!TitleWidgetClass) return; // é∏îsÇµÇΩÇÁâΩÇ‡ÇπÇ∏èIóπ.
	TitleWidget = CreateWidget<UTMMATitleWidget>(GetWorld(), TitleWidgetClass);
	if (!TitleWidget) return;
	TitleWidget->AddToViewport();
} 

