// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAGetItemWidget.h"

void UTMMAGetItemWidget::SetGetItemText(FString InTextString)
{
	GetItemText->SetText(FText::FromString(InTextString));
}

void UTMMAGetItemWidget::SetGetItemTextColor(FLinearColor InItemTextBaseColor)
{
	ItemTextBaseColor = InItemTextBaseColor;
	GetItemText->SetColorAndOpacity(InItemTextBaseColor);
}

void UTMMAGetItemWidget::AddViewCountAndChangeTextColor()
{
	int ViewCountMod = (ViewCount % 4);
	FLinearColor ViewedItemTextColor = ItemTextBaseColor;
	switch (ViewCountMod)
	{
	case 2:
	case 3:
		ViewedItemTextColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.1f);
		break;
	default:
		break;
	}
	GetItemText->SetColorAndOpacity(ViewedItemTextColor);
}