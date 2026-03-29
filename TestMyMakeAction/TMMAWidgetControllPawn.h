// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameUIBase.h"
#include "TMMAPlayerInterfaceBase.h"
#include "TMMAWidgetControllPawn.generated.h"

UCLASS()
class TESTMYMAKEACTION_API ATMMAWidgetControllPawn : public APawn, public IPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATMMAWidgetControllPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetControllWidget(UGameUIBase* InGameUi);

	UFUNCTION(BlueprintPure)
	UGameUIBase* GetControllWidget() const {
		return ControllGameUI;
	}

private:
	UGameUIBase* ControllGameUI;
};
