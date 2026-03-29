// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMADirectionWidget.h"

void UTMMADirectionWidget::ChangeColorText()
{
	int ViewColorType = (ViewCount % 3) + 1;
//	if (L_DirectionText != nullptr) {
		FSlateColor ViewTextColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		switch (ViewColorType) {
			case 2:
				ViewTextColor = FSlateColor(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
				break;
			case 3:
				ViewTextColor = FSlateColor(FLinearColor(1.0f, 0.5f, 0.0f, 1.0f));
				break;
			default:
				break;
		}
		L_DirectionText->SetColorAndOpacity(ViewTextColor);
		R_DirectionText->SetColorAndOpacity(ViewTextColor);
//	}
}

void UTMMADirectionWidget::AddViewCountAndViewCheck()
{
	if (IsView == true) {
		ViewCount++;
		if (ViewCount > LimitViewCount) {
			IsView = false;
			this->SetVisibility(ESlateVisibility::Hidden);
			ViewCount = 0;
		}
	}
}

void UTMMADirectionWidget::SetDirectionType(EDirectionType InDirectionType)
{
	DirectionType = InDirectionType;
}

void UTMMADirectionWidget::SetDirectionTypeAndText(EDirectionType InDirectionType)
{
	SetDirectionType(InDirectionType);
	// ‚ ‚ç‚©‚¶‚ß‰Šú‚ÌÝ’è‚É‚µ‚Ä‚¨‚­.
	L_DirectionText->SetRenderTransformAngle(0.0);
	R_DirectionText->SetRenderTransformAngle(0.0);
	FString L_DirectionStr = FString::Printf(TEXT("GO"));
	FString R_DirectionStr = FString::Printf(TEXT(" >>>"));
	switch (InDirectionType)
	{
		case EDirectionType::Left:
			L_DirectionStr = FString::Printf(TEXT("<<< "));
			R_DirectionStr = FString::Printf(TEXT("GO"));
			break;
		case EDirectionType::Right:
			break;
		case EDirectionType::Up:
//			L_DirectionText->SetRenderTransformAngle(-90.0);
			if (IsLeftSide == true) {
				L_DirectionStr = FString::Printf(TEXT(" >>>"));
				R_DirectionStr = FString::Printf(TEXT("GO"));
				L_DirectionText->SetRenderTransformAngle(-90.0);
			}
			else {
				L_DirectionStr = FString::Printf(TEXT("GO"));
				R_DirectionStr = FString::Printf(TEXT(" >>>"));
				R_DirectionText->SetRenderTransformAngle(-90.0);
			}
			break;
		case EDirectionType::Down:
//			L_DirectionText->SetRenderTransformAngle(90.0);
			if (IsLeftSide == true) {
				L_DirectionStr = FString::Printf(TEXT(" >>>"));
				R_DirectionStr = FString::Printf(TEXT("GO"));
				L_DirectionText->SetRenderTransformAngle(90.0);
			}
			else {
				L_DirectionStr = FString::Printf(TEXT("GO"));
				R_DirectionStr = FString::Printf(TEXT(" >>>"));
				R_DirectionText->SetRenderTransformAngle(90.0);
			}
			break;
		default:
			break;
	}
	L_DirectionText->SetText(FText::FromString(L_DirectionStr));
	R_DirectionText->SetText(FText::FromString(R_DirectionStr));
}

void UTMMADirectionWidget::SetIsView(bool InIsView)
{
	IsView = InIsView;
}

void UTMMADirectionWidget::SetIsLeftSide(bool InIsLeftSide) {
	IsLeftSide = InIsLeftSide;
}

