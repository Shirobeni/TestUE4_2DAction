// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/GameUIBase.h"
#include "TMMAItemButtonBase.h"
#include "TMMAItemButton.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemButtonRow {
	GENERATED_BODY()
public:
	int row = 0;

	int column = 0;

	bool isSelected;
};


UENUM(BlueprintType)
enum class ETMMACursorAction : uint8 {
	BUTTON_NONE			UMETA(DisplayName = "–³"),
	BUTTON_DECIDE		UMETA(DisplayName = "Œˆ’è"),
	BUTTON_SELECTED		UMETA(DisplayName = "‘I‘ð’†"),
	BUTTON_UNSELECTED	UMETA(DisplayName = "”ñ‘I‘ð’†"),
};


UCLASS()
class TESTMYMAKEACTION_API UTMMAItemButton : public UTMMAItemButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ButtonAction(ETMMACursorAction InAction);

//	UFUNCTION(BlueprintCallable)
//	void BindButton(UButton* InButton);

	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);

	UFUNCTION(BlueprintPure)
	UButton* GetMenuButton() {
		return MenuButton;
	}

	UFUNCTION(BlueprintPure)
	UTextBlock* GetButtonText() {
		return ButtonText;
	}

	void SetRowAndColumn(int InRow, int InColumn);

	UFUNCTION(BlueprintCallable)
	void SetIsSelected(bool InIsSelected);

	UFUNCTION(BlueprintPure)
	const bool GetIsSelected() const {
		return ButtonRow.isSelected;
	}

	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MenuButton = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ButtonText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemButtonRow ButtonRow;

};
