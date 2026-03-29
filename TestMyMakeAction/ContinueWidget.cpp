// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinueWidget.h"

void UContinueWidget::ReduceContinueTime() {
	ContinueTime -= 0.1f;
	if (ContinueTime < 0.0f) {
		InitContinueTime();
		ReduceContinueCount();
	}
}

void UContinueWidget::InitContinueTime() {
	ContinueTime = 10.0f;
}

void UContinueWidget::InitContinueCount() {
	ContinueCount = 10;
}

void UContinueWidget::ReduceContinueCount() {
	ContinueCount -= 1;
}

void UContinueWidget::SetItemList(UTMMAItemList* InItemList)
{
	ItemList = InItemList;
}

