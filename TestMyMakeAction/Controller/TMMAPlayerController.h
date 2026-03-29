// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestMyMakeAction/TMMAPlayerInterfaceBase.h"
#include "TestMyMakeAction/TMMAPlayerBase.h"
#include "TestMyMakeAction/TMMAWidgetControllPawn.h"
#include "TMMAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetControllPlayer(ATMMAPlayerBase* InControllPlayer);

	UFUNCTION(BlueprintPure)
	ATMMAPlayerBase* GetControllPlayer() const
	{
		return ControllPlayer;
	}

	UFUNCTION(BlueprintCallable)
	void SetControllPawn(APawn* InControllPawn);

	UFUNCTION(BlueprintPure)
	APawn* GetControllPawn() const
	{
		return ControllPawn;
	}

protected:
	ATMMAPlayerBase* ControllPlayer;

	APawn* ControllPawn;

};
