// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAItemButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTMMAItemButton::ButtonAction(ETMMACursorAction InAction) {
	switch (InAction) {
		case ETMMACursorAction::BUTTON_DECIDE :
			MenuButton->OnPressed;
			break;
		case ETMMACursorAction::BUTTON_SELECTED :
			MenuButton->OnHovered;
			break;
		case ETMMACursorAction::BUTTON_UNSELECTED :
			MenuButton->OnUnhovered;
			break;
		default :
			break;
	}
}

//void UTMMAItemButton::BindButton(UButton* InButton)
//{
//
//}

void UTMMAItemButton::SetButtonText(FText InText)
{
	ButtonText->SetText(InText);
}

void UTMMAItemButton::SetRowAndColumn(int InRow, int InColumn)
{
	ButtonRow.row = InRow;
	ButtonRow.column = InColumn;
}

void UTMMAItemButton::SetIsSelected(bool InIsSelected)
{
	ButtonRow.isSelected = InIsSelected;
}