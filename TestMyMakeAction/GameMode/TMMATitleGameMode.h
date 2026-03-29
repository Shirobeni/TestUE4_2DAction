// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestMyMakeAction/TMMAWidgetControllPawn.h"
#include "TMMATitleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void StartGame();

public:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<ATMMAWidgetControllPawn> SoftWidgetControllPawnClass;

private:
	ATMMAWidgetControllPawn* WidgetContorllPawn;
};
