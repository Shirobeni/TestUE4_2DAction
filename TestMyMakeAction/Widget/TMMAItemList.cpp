// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAItemList.h"

void UTMMAItemList::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTMMAItemList::SetSelectedRowColumnIndex(int InRow, int InColumn, int InIndex)
{
	if (UniformItemGridPanel != nullptr) {
		SelectedButtonRowColumn.row = InRow;
		SelectedButtonRowColumn.column = InColumn;
		SelectedButtonRowColumn.index = InIndex;
	}
}

void UTMMAItemList::CreateButtonList(int InCount)
{
	int LimitItemCount = MaxRow * MaxColumn;
	if (UniformItemGridPanel != nullptr) {
		UniformItemGridPanel->ClearChildren();
		ItemButtonList.Reset();
		if (ItemButton != nullptr) {
			int idx = 0;
			for (int i = 0; i < InCount; i++)
			{
				if (i <= LimitItemCount) {
					UTMMAItemButton* LItemButton = CreateWidget<UTMMAItemButton>(GetWorld(), ItemButton);
					LItemButton->SetItemIndex(i);
					int TurnBackMax = 0;
					if (IsColumn == true) {
						TurnBackMax = MaxColumn;
						UniformItemGridPanel->AddChildToUniformGrid(LItemButton, idx, i);
						LItemButton->ButtonRow.row = idx;
						LItemButton->ButtonRow.column = i;
						RealMaxRow = idx;
						RealMaxColumn = i;
					}
					else {
						TurnBackMax = MaxRow;
						UniformItemGridPanel->AddChildToUniformGrid(LItemButton, i, idx);
						LItemButton->ButtonRow.row = i;
						LItemButton->ButtonRow.column = idx;
						RealMaxRow = i;
						RealMaxColumn = idx;
					}
					ItemButtonList.Add(LItemButton);
					if (((i + 1) % TurnBackMax) == 0) {
						idx++;
					}
				}
			}
		}
	}
}

void UTMMAItemList::SelectButtonByInput(EInputDirection InputDirection, int AddParam)
{
	//FSelectedButtonRowColumn Now
}

void UTMMAItemList::SelectedButtonByRowColumn(int InRow, int InColumn, APlayerController* InPlayerController)
{
	if (InPlayerController != nullptr) {
		for (int i = 0; i < ItemButtonList.Num(); i++) {
			if (ItemButtonList.IsValidIndex(i)) {
				UTMMAItemButton* LItemButton = ItemButtonList[i];
				if ((LItemButton->ButtonRow.row == InRow) && (LItemButton->ButtonRow.column == InColumn)) {
					SetSelectedRowColumnIndex(InRow, InColumn, LItemButton->GetItemIndex());
					LItemButton->SetUserFocus(InPlayerController);
					LItemButton->SetIsSelected(true);
					UE_LOG(LogTemp, Log, TEXT("Row=%d"), LItemButton->ButtonRow.row);
					UE_LOG(LogTemp, Log, TEXT("Column=%d"), LItemButton->ButtonRow.column);
				}
				else {
					LItemButton->SetIsSelected(false);
				}
			}
		}
	}
}

void UTMMAItemList::SetUniformGridPanel() {
	CreateButtonList(CreateItemNum);
}

void UTMMAItemList::AddSelectRowColumn(int AddRow, int AddColumn, APlayerController* InPlayerController)
{
	int NextRow = SelectedButtonRowColumn.row + AddRow;
	if (NextRow > RealMaxRow) {
		NextRow = 0;
	}
	else if (NextRow < 0) {
		NextRow = RealMaxRow;
	}
	int NextColumn = SelectedButtonRowColumn.column + AddColumn;
	if (NextColumn > RealMaxColumn) {
		NextColumn = 0;
	}
	else if (NextColumn < 0) {
		NextColumn = RealMaxColumn;
	}
	SelectedButtonByRowColumn(NextRow, NextColumn, InPlayerController);
}

