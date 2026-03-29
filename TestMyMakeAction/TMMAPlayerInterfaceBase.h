// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TMMAPlayerInterfaceBase.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UPlayerInterface : public UInterface 
{
	GENERATED_BODY()
};

class IPlayerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void Left();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void LeftRun(float InAxisValue, float& OutAxisValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void Right();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void RightRun(float InAxisValue, float& OutAxisValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void Up();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void UpMove(float InAxisValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void Down();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void DownMove(float InAxisValue);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void LetGoDown();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void PressA();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void LetGoA();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void PressB();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void LetGoB();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputEvent")
	void PressC();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "StatusEvent")
	void PowerUp();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "StatusEvent")
	void PlayerDamage(int DamageParam);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OtherEvent")
	void InsertCredit();


};

class TESTMYMAKEACTION_API TMMAPlayerInterfaceBase
{
public:
	TMMAPlayerInterfaceBase();
	~TMMAPlayerInterfaceBase();
};
