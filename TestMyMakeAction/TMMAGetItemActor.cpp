// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAGetItemActor.h"

void ATMMAGetItemActor::SetGetItemWidgetBySoft()
{
	TSubclassOf<UTMMAGetItemWidget> GetItemWidgetClass = GetItemWidgetSoftClass.LoadSynchronous();
	GetItemWidget = CreateWidget<UTMMAGetItemWidget>(GetWorld(), GetItemWidgetClass);
}

void ATMMAGetItemActor::SetItemType(EGetItemType InGetItemType)
{
	GetItemType = InGetItemType;
}

void ATMMAGetItemActor::SetItemTypeAndText(EGetItemType InGetItemType, int ItemLevel)
{
	SetItemType(InGetItemType);
	if (GetItemWidget != nullptr) {
		FString DirectionStr = FString::Printf(TEXT("POWER UP"));
		FLinearColor ViewTextColor = FLinearColor(1.0f, 0.1f, 0.0f, 1.0f);
		switch (GetItemType)
		{
		case EGetItemType::PowerUp:
			if (ItemLevel >= 3) {
				DirectionStr = FString::Printf(TEXT("1000 Pts."));
			}
			break;
		case EGetItemType::Rapid:
			DirectionStr = FString::Printf(TEXT("RAPID"));
			ViewTextColor = FLinearColor(1.0f, 0.2f, 0.0f, 1.0f);
			break;
		case EGetItemType::Homing:
			DirectionStr = FString::Printf(TEXT("HOMING"));
			ViewTextColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
			break;
		case EGetItemType::Fire:
			DirectionStr = FString::Printf(TEXT("FIRE"));
			ViewTextColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		case EGetItemType::Grenade:
			DirectionStr = FString::Printf(TEXT("GRENADE"));
			ViewTextColor = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
			break;
		case EGetItemType::Laser:
			DirectionStr = FString::Printf(TEXT("LASER"));
			ViewTextColor = FLinearColor(0.0f, 0.1f, 1.0f, 1.0f);
			break;
		case EGetItemType::Burst:
			DirectionStr = FString::Printf(TEXT("GET BURST"));
			ViewTextColor = FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);			
			break;
		case EGetItemType::Life:
			DirectionStr = FString::Printf(TEXT("LIFE UP"));
			ViewTextColor = FLinearColor(1.0f, 0.1f, 0.3f, 1.0f);
		default:
			break;
		};
		GetItemWidget->SetGetItemText(DirectionStr);
		GetItemWidget->SetGetItemTextColor(ViewTextColor);
	}

}