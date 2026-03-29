// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TMMAPlayerCameraBase.generated.h"

UCLASS()
class TESTMYMAKEACTION_API ATMMAPlayerCameraBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMMAPlayerCameraBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void MainMovingCamera();

	UFUNCTION(BlueprintCallable)
	void MovingCamera();

	// YŽ²‚Ì‚ÝŽ©—RˆÚ“®
	UFUNCTION(BlueprintCallable)
	void MovingCameraYMighty();

	// ZŽ²‚Ì‚ÝŽ©—RˆÚ“®
	UFUNCTION(BlueprintCallable)
	void MovingCameraZMighty();


	UFUNCTION(BlueprintCallable)
	void MovingCameraYZMighty();

	UFUNCTION(BlueprintCallable)
	void LockCamera(AActor* InLockCollisionActor);

	UFUNCTION(BlueprintCallable)
	void SetCameraPosition(FVector InCameraPosition);

	UFUNCTION(BlueprintCallable)
	void SetCameraVector(FVector InCameraVector);

	UFUNCTION(BlueprintCallable)
	void SetRestartCamera(FVector InCameraVector);


	UFUNCTION(BlueprintPure)
	const FVector GetCameraPosition() const
	{
		return CameraPosition;
	}

	UFUNCTION(BlueprintPure)
	const FVector GetCameraVector() const
	{
		return CameraVector;
	}

	UFUNCTION(BlueprintCallable)
		void SetYMightyFlag(bool InYMightyFlag);

	UFUNCTION(BlueprintPure)
		const bool GetYMightyFlag() const
	{
		return YMightyFlag;
	}

	UFUNCTION(BlueprintCallable)
	void SetZMightyFlag(bool InZMightyFlag);

	UFUNCTION(BlueprintPure)
	const bool GetZMightyFlag() const
	{
		return ZMightyFlag;
	}

	UFUNCTION(BlueprintCallable)
	void InitCameraMightyFlag();



public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CameraPosition = FVector(0.0, 0.0, 0.0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CameraVector = FVector(0.0, 0.0, 0.0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool YMightyFlag = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ZMightyFlag = false;

};
