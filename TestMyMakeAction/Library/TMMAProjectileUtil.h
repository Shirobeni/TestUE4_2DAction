// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TMMAProjectileUtil.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UTMMAProjectileUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void SetInitializeAndMaxSpeed(UProjectileMovementComponent* InProjectileComp, float InInitializeSpeed, bool IsChangeInitSpd, float InMaxSpeed, bool IsChangeMaxSpeed);

	UFUNCTION(BlueprintCallable)
	static void MultiplyVelocityForFloat(UProjectileMovementComponent* InProjectileComp, float MultplyParam);

	UFUNCTION(BlueprintCallable)
	static void SetHomingTargetForActor(UProjectileMovementComponent* InProjectileComp, AActor* InTargetActor);

	UFUNCTION(BlueprintCallable)
	static void SetHomingTargetForActorAndFlag(UProjectileMovementComponent* InProjectileComp, AActor* InTargetActor, bool IsHoming);

	UFUNCTION(BlueprintCallable)
	static void SetVelocity(UProjectileMovementComponent* InProjectileComp, FVector InVelocity);

	UFUNCTION(BlueprintCallable)
	static void AddVelocity(UProjectileMovementComponent* InProjectileComp, FVector InAddVelocity);

	UFUNCTION(BlueprintCallable)
	static void MultiplyVelocity(UProjectileMovementComponent* InProjectileComp, float MultiplyX, float MultiplyY, float MultiplyZ);

};
