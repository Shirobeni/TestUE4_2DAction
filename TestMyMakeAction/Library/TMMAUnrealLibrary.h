// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TMMAUnrealLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TESTMYMAKEACTION_API UTMMAUnrealLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// アクタ生成をソフト参照で行う.
	UFUNCTION(BlueprintCallable)
	static void SpawnActorBySoft(UObject* Object, TSoftClassPtr<AActor> SoftActor, FTransform Transform, AActor*& SpawnedActor);

	// パーティクル生成をソフト参照で行う.
	UFUNCTION(BlueprintCallable)
	static void SpawnParticleBySoft(UObject* Object, TSoftObjectPtr<UParticleSystem> ParticleSoft, FVector InVector, FVector InScale);
	
	// SE生成をソフト参照で行う
	UFUNCTION(BlueprintCallable)
	static void SpawnSeBySoft(UObject* Object, TSoftObjectPtr<USoundBase> SoftSe);

	// nullptrチェックとIsValidチェックを段階的に行う.
	static bool GetIsNotNullPtrAndIsValid(UObject* Object)
	{
		if (Object != nullptr) {
			if (IsValid(Object) == true) {
				return true;
			}
		}
		return false;
	}



};
