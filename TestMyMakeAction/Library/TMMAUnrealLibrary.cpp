// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAUnrealLibrary.h"

void UTMMAUnrealLibrary::SpawnActorBySoft(UObject* Object, TSoftClassPtr<AActor> SoftActor, FTransform Transform, AActor*& SpawnedActor)
{
	if (SoftActor != nullptr && Object != nullptr) {
		TSubclassOf<AActor> ActorClass = SoftActor.LoadSynchronous();
		SpawnedActor = Object->GetWorld()->SpawnActor<AActor>(ActorClass, Transform);
		if (IsValid(SpawnedActor) == true) {
			SpawnedActor->SetActorTransform(Transform);
		}
	}
}

void UTMMAUnrealLibrary::SpawnParticleBySoft(UObject* Object, TSoftObjectPtr<UParticleSystem> ParticleSoft, FVector InVector, FVector InScale)
{
	if (Object != nullptr) {
		UParticleSystem* Particle = ParticleSoft.LoadSynchronous();
		// 各スケールのベクトルが0以下の場合は1に設定.
		if (InScale.X <= 0.0) {
			InScale.X = 1.0;
		}
		if (InScale.Y <= 0.0) {
			InScale.Y = 1.0;
		}
		if (InScale.Z <= 0.0) {
			InScale.Z = 1.0;
		}
		UGameplayStatics::SpawnEmitterAtLocation(Object->GetWorld(), Particle, InVector, FRotator(0.0f, 0.0f, 0.0f), InScale, true, EPSCPoolMethod::None, true);
	}
}

void UTMMAUnrealLibrary::SpawnSeBySoft(UObject* Object, TSoftObjectPtr<USoundBase> SoftSe)
{
	if (Object != nullptr) {
		USoundBase* Se = SoftSe.LoadSynchronous();
		UGameplayStatics::PlaySound2D(Object->GetWorld(), Se, 1.0f, 1.0f, 0.0f, nullptr);
	}
}