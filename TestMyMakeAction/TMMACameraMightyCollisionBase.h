// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TMMAPlayerCameraBase.h"
#include "TMMACameraMightyCollisionBase.generated.h"

UENUM(BlueprintType)
enum class EMightyType : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	YOnly UMETA(DisplayName = "YOnly"),
	ZOnly UMETA(DisplayName = "ZOnly"),
	YAndZ UMETA(DisplayName = "YAndZ"),
};


UCLASS()
class TESTMYMAKEACTION_API ATMMACameraMightyCollisionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMMACameraMightyCollisionBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerCamera(ATMMAPlayerCameraBase* InPlayerCamera);

	UFUNCTION(BlueprintPure)
	ATMMAPlayerCameraBase* GetPlayerCamera() const
	{
		return PlayerCamera;
	}

	UFUNCTION(BlueprintCallable)
	void SwitchMighty();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATMMAPlayerCameraBase* PlayerCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MightyStatus")
	EMightyType MightyStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MightyStatus")
	bool IsMightyFlag = false;

};
