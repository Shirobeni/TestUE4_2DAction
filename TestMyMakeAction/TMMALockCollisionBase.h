// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Library/TMMAActorLibrary.h"
#include "TestMyMakeActionGameModeBase.h"
#include "GameState/TMMAGameStateBase.h"
#include "TestMyMakeAction/Actor/TMMAActorBase.h"
#include "TMMALockCollisionBase.generated.h"

UCLASS()
class TESTMYMAKEACTION_API ATMMALockCollisionBase : public ATMMAActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMMALockCollisionBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetIsLock(bool InIsLock);

	UFUNCTION(BlueprintPure)
	const bool GetIsLock() const
	{
		return IsLock;
	}

	UFUNCTION(BlueprintCallable)
	void SetIsVertical(bool InIsVertical);

	UFUNCTION(BlueprintPure)
	const bool GetIsVertical() const
	{
		return IsVertical;
	}

	UFUNCTION(BlueprintCallable)
	void SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode);

	UFUNCTION(BlueprintPure)
	ATestMyMakeActionGameModeBase* GetMainGameMode() const
	{
		return MainGameMode;
	}

	UFUNCTION(BlueprintCallable)
	void SetMainGameState(ATMMAGameStateBase* InMainGameState);

	UFUNCTION(BlueprintPure)
	ATMMAGameStateBase* GetMainGameState() const
	{
		return MainGameState;
	}

public:
	bool IsLock = false;

	bool IsVertical = false;

	ATestMyMakeActionGameModeBase* MainGameMode;

	ATMMAGameStateBase* MainGameState;
};
