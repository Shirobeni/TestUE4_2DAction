// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../TMMAEnemyBase.h"
#include "../Library/TMMAActorLibrary.h"
#include "TMMAEnemyAiBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API ATMMAEnemyAiBase : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
		UFUNCTION(BlueprintCallable)
		void SetControllEnemy(ATMMAEnemyBase* InControllEnemy);

		UFUNCTION(BlueprintPure)
		ATMMAEnemyBase* GetControllEnemy() const {
			return ControlleEnemy;
		}

		UFUNCTION(BlueprintCallable)
			void SetIsArrivedPoint(bool InIsArrivedPoint);

		UFUNCTION(BlueprintPure)
		const bool GetIsArrivedPoint() const 
		{
			return IsArrivedPoint;
		}

		UFUNCTION(BlueprintCallable)
		void SetIsAbleMove(bool InIsAbleMove);

		UFUNCTION(BlueprintPure)
		const bool GetIsAbleMove() const
		{
			return IsAbleMove;
		}

		UFUNCTION(BlueprintCallable)
		void SetIsUnlimitedDistance(bool InIsUnlimitedDistance);

		UFUNCTION(BlueprintCallable)
		const bool GetIsUnlimitedDistanc() const
		{
			return IsUnlimitedDistance;
		}



protected:
	//コントロール対象の敵アクタ
		ATMMAEnemyBase* ControlleEnemy;

	// 目的地へ到達したか
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsArrivedPoint;

	// 距離関係なく動くかどうか
		bool IsUnlimitedDistance = true;

	// 動いてもOKか
		bool IsAbleMove;
};
