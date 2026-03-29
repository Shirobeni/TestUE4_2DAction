// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestMyMakeAction/GameUIBase.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TMMAItemButton.h"
#include "TMMAItemButtonBase.h"
#include "TMMAItemList.generated.h"

DECLARE_DELEGATE_OneParam(FPressedButton, const UButton*)

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSelectedButtonRowColumn {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectdButtonParam")
	int row = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectdButtonParam")
	int column = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectdButtonParam")
	int index = 0;

};

UENUM(BlueprintType)
enum class EInputDirection : uint8 {
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
};



UCLASS()
class TESTMYMAKEACTION_API UTMMAItemList : public UGameUIBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	//virtual void NativeTick(const FGeometry&, float) override;

	UFUNCTION(BlueprintCallable)
	void CreateButtonList(int InCount);

	UFUNCTION(BlueprintCallable)
	void SetUniformGridPanel();

	UFUNCTION(BlueprintPure)
	const TArray<UTMMAItemButton*> GetItemList() const
	{
		return ItemButtonList;
	}
	UFUNCTION(BlueprintCallable)
	void SetSelectedRowColumnIndex(int InRow, int InColumn, int InIndex);

	UFUNCTION(BlueprintCallable)
	void SelectedButtonByRowColumn(int InRow, int InColumn, APlayerController* InPlayerController);

	UFUNCTION(BlueprintCallable)
	void SelectButtonByInput(EInputDirection InputDirection, int AddParam);

	UFUNCTION(BlueprintPure)
	FSelectedButtonRowColumn GetSelectedButtonRowColumn() const
	{
		return SelectedButtonRowColumn;
	}

	UFUNCTION(BlueprintCallable)
	void AddSelectRowColumn(int AddRow, int AddColumn, APlayerController* InPlayerController);

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UOverlay* ItemOverlay = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UUniformGridPanel* UniformItemGridPanel = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTMMAItemButton> ItemButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTMMAItemButton*> ItemButtonList;


	// ê›íËè„ÇÃç≈ëÂRow, Column
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxRow = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxColumn = 0;

	// é¿ç€Ç…ê›íËÇ≥ÇÍÇΩç≈ëÂRow, Column
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RealMaxRow = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RealMaxColumn = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CreateItemNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsColumn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSelectedButtonRowColumn SelectedButtonRowColumn;


private:
	FPressedButton OnDecideButton;
};
