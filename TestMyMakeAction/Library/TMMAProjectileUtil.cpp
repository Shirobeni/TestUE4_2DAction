// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAProjectileUtil.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UTMMAProjectileUtil::SetInitializeAndMaxSpeed(UProjectileMovementComponent* InProjectileComp, float InInitializeSpeed, bool IsChangeInitSpd, float InMaxSpeed, bool IsChangeMaxSpeed) 
{
	if (IsChangeInitSpd)
	{
		InProjectileComp->InitialSpeed = InInitializeSpeed;
	}
	if (IsChangeMaxSpeed)
	{
		InProjectileComp->MaxSpeed = InMaxSpeed;
	}
}

void UTMMAProjectileUtil::MultiplyVelocityForFloat(UProjectileMovementComponent* InProjectileComp, float MultplyParam)
{
	if (MultplyParam > 0.0) {
		InProjectileComp->Velocity *= MultplyParam;
	}
}

void UTMMAProjectileUtil::SetHomingTargetForActor(UProjectileMovementComponent* InProjectileComp, AActor* InTargetActor)
{
	if (InTargetActor != nullptr) {
		USceneComponent* TargetActorComponent = NewObject<USceneComponent>(InTargetActor);
		InProjectileComp->HomingTargetComponent = TargetActorComponent;
	}
}

void UTMMAProjectileUtil::SetHomingTargetForActorAndFlag(UProjectileMovementComponent* InProjectileComp, AActor* InTargetActor, bool IsHoming)
{
	if (InTargetActor != nullptr) {
		SetHomingTargetForActor(InProjectileComp, InTargetActor);
		InProjectileComp->bIsHomingProjectile = IsHoming;
	}
}

void UTMMAProjectileUtil::SetVelocity(UProjectileMovementComponent* InProjectileComp, FVector InVelocity)
{
	InProjectileComp->Velocity = InVelocity;
}

void UTMMAProjectileUtil::AddVelocity(UProjectileMovementComponent* InProjectileComp, FVector InAddVelocity)
{
	InProjectileComp->Velocity += InAddVelocity;
}

void UTMMAProjectileUtil::MultiplyVelocity(UProjectileMovementComponent* InProjectileComp, float MultiplyX, float MultiplyY, float MultiplyZ)
{
	// ŠeŠ|‚¯”‚ª0ˆÈ‰º‚Ì’l‚Í1‚ğİ’è.
	if (MultiplyX <= 0.0) {
		MultiplyX = 1.0;
	}
	if (MultiplyY <= 0.0) {
		MultiplyY = 1.0;
	}
	if (MultiplyZ <= 0.0) {
		MultiplyZ = 1.0;
	}
	FVector ProjectileVelocity = InProjectileComp->Velocity;
	ProjectileVelocity.X = ProjectileVelocity.X * MultiplyX;
	ProjectileVelocity.Y = ProjectileVelocity.Y * MultiplyY;
	ProjectileVelocity.Z = ProjectileVelocity.Z * MultiplyZ;
	InProjectileComp->Velocity = ProjectileVelocity;
}

