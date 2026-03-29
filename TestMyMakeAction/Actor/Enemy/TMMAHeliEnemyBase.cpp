// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAHeliEnemyBase.h"

void ATMMAHeliEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle _TimerHandle;
	GetWorldTimerManager().SetTimer(_TimerHandle, this, &ATMMAHeliEnemyBase::ShotMissile, 0.4f, true);
}

void ATMMAHeliEnemyBase::AttachChildCompByAsset()
{
	if (GetMesh() != nullptr) {
		int idx = 0;
		for (USkeletalMesh* ChildSkeltalMesh : ChildSkeltalMeshList) {
			if (ChildSkeltalMesh != nullptr) {
				FString MeshString = FString::Printf(TEXT("ChildMesh%d"),idx);
				USkeletalMeshComponent* ChildSkeltaleMeshComponent = NewObject<USkeletalMeshComponent>(this);
				ChildSkeltaleMeshComponent->RegisterComponent();
				ChildSkeltaleMeshComponent->SetSkeletalMesh(ChildSkeltalMesh);
				ChildSkeltaleMeshComponent->AttachTo(GetMesh(), TEXT("None"), EAttachLocation::KeepWorldPosition, true);
				idx++;
			}
		}
	}
}

void ATMMAHeliEnemyBase::MoveByAimPlayer()
{
	if (GetInDistanceAtPlayerY(100, -100.0)) {
		FVector PlayerVector = FVector(0.0f, 0.0f, 0.0f);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
		if (IsValid(PlayerPawn)){
			PlayerVector = PlayerPawn->GetActorLocation();
		}
		FVector AimToPlayer = GetAimToPlayer(GetActorLocation(), PlayerVector);
		AddMovementInput(FVector(0.0f, AimToPlayer.Y, 0.0), 0.2f);
	}
}

void ATMMAHeliEnemyBase::ShotMissile()
{
	if (WasRecentlyRendered(0.0)) {
		FTransform MissileTransform;
		MissileTransform.SetLocation(GetActorLocation());
		MissileTransform.SetRotation(FQuat(FRotator(1.0f, 1.0f, 1.0f)));
		MissileTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
		AActor* MissileActor;
		UTMMAUnrealLibrary::SpawnActorBySoft(this, SpawnActorSoftList[0], MissileTransform, MissileActor);
	}
}

void ATMMAHeliEnemyBase::FunctionByTimerEvent()
{
	if (WasRecentlyRendered(0.0)) {
		MoveByAimPlayer();
//		FTimerHandle _TimerHandle;
//		GetWorldTimerManager().SetTimer(_TimerHandle, this, &ATMMAHeliEnemyBase::ShotMissile, 0.4f, false);
	}
}