// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMADirectionCollisionObject.h"

void ATMMADirectionCollisionObject::SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode)
{
	MainGameMode = InMainGameMode;
}

void ATMMADirectionCollisionObject::ConvertDirectTypeToNavigationDirect(ENavigationDirect& NavigationDirect)
{
	NavigationDirect = ENavigationDirect::Right;
	switch (DirectionType) {
		case EDirectionType::Left :
			NavigationDirect = ENavigationDirect::Left;
			break;
		case EDirectionType::Up:
			NavigationDirect = ENavigationDirect::Up;
			break;
		case EDirectionType::Down:
			NavigationDirect = ENavigationDirect::Down;
			break;
		default:
			break;
	}
}

void ATMMADirectionCollisionObject::SetIsLeftPosition(bool InIsLeftPosition)
{
	IsLeftPosition = InIsLeftPosition;
}

void ATMMADirectionCollisionObject::SetDirectPositionToGameMode()
{
	if (MainGameMode != nullptr) {
		if (IsLeftPosition == true) {
			MainGameMode->SetIsDirectLeftSide(true);
		}
		else {
			MainGameMode->SetIsDirectLeftSide(false);
		}
	}
}