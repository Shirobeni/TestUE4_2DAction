// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TMMAObjectBase.h"
#include "TestMyMakeAction/TestMyMakeActionGameModeBase.h"
#include "TestMyMakeAction/Widget/TMMADirectionWidget.h"
#include "TMMADirectionCollisionObject.generated.h"

/**
 * 
 */

UCLASS()
class TESTMYMAKEACTION_API ATMMADirectionCollisionObject : public ATMMAObjectBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode);

	UFUNCTION(BlueprintPure)
	ATestMyMakeActionGameModeBase* GetMainGameMode() const
	{
		return MainGameMode;
	}

	UFUNCTION(BlueprintPure)
	EDirectionType GetDirectionType() const
	{
		return DirectionType;
	}

	UFUNCTION(BlueprintCallable)
	void ConvertDirectTypeToNavigationDirect(ENavigationDirect& NavigationDirect);

	UFUNCTION(BlueprintCallable)
	void SetIsLeftPosition(bool InIsLeftPosition);

	UFUNCTION(BlueprintPure)
		const bool GetIsLeftPosition() const
	{
		return IsLeftPosition;
	}

	UFUNCTION(BlueprintCallable)
		void SetDirectPositionToGameMode();

public:
	UPROPERTY(EditAnywhere)
	EDirectionType DirectionType = EDirectionType::Right;
	
	UPROPERTY(EditAnywhere)
	bool IsLeftPosition = false;

private:
	ATestMyMakeActionGameModeBase* MainGameMode;

};
