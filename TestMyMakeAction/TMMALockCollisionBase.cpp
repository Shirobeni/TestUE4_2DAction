// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMALockCollisionBase.h"

// Sets default values
ATMMALockCollisionBase::ATMMALockCollisionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMMALockCollisionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMMALockCollisionBase::Tick(float DeltaTime)
{
	if (IsVertical == true) {
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
		if (IsValid(PlayerPawn))
		{
			FVector LockCollisionLocation = this->GetActorLocation();
			FVector PlayerLocation = PlayerPawn->GetActorLocation();
			float SubLocationZ = PlayerLocation.Z - LockCollisionLocation.Z;
			if (SubLocationZ >= 300.0) {
				FVector SetVector = FVector(LockCollisionLocation.X, LockCollisionLocation.Y, (SubLocationZ + LockCollisionLocation.Z + 100));
				this->SetActorLocation(SetVector);
			}
			else {
				if (SubLocationZ <= -300) {
					FVector SetVector = FVector(LockCollisionLocation.X, LockCollisionLocation.Y, (LockCollisionLocation.Z - SubLocationZ));
					this->SetActorLocation(SetVector);
				}
			}

		}
	}
	Super::Tick(DeltaTime);

}

void ATMMALockCollisionBase::SetIsLock(bool IsInLock)
{
	IsLock = IsInLock;
}

void ATMMALockCollisionBase::SetIsVertical(bool IsInVertical)
{
	IsVertical = IsInVertical;
}

void ATMMALockCollisionBase::SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode)
{
	MainGameMode = InMainGameMode;
}
void ATMMALockCollisionBase::SetMainGameState(ATMMAGameStateBase* InMainGameState)
{
	MainGameState = InMainGameState;
}