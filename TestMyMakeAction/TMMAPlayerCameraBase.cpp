// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAPlayerCameraBase.h"
#include "Kismet/GameplayStatics.h"
#include "TMMAPlayerBase.h"

// Sets default values
ATMMAPlayerCameraBase::ATMMAPlayerCameraBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMMAPlayerCameraBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMMAPlayerCameraBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMMAPlayerCameraBase::SetCameraPosition(FVector InCameraPosition)
{
	CameraPosition = InCameraPosition;
}

void ATMMAPlayerCameraBase::SetCameraVector(FVector InCameraVector)
{
	CameraVector = InCameraVector;
}

void ATMMAPlayerCameraBase::SetRestartCamera(FVector InCameraVector)
{
	SetCameraPosition(InCameraVector);
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(this, 0.0);
}

void ATMMAPlayerCameraBase::MainMovingCamera()
{
	if (YMightyFlag == true && ZMightyFlag == true)
	{
		MovingCameraYZMighty();
	}
	else if (YMightyFlag == true) {
		MovingCameraYMighty();
	}
	else if (ZMightyFlag == true)
	{
		MovingCameraZMighty();
	} 
	else {
		MovingCamera();
	}

}

void ATMMAPlayerCameraBase::MovingCamera()
{
	APawn* aPlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	if (ATMMAPlayerBase* PlayerCharacter = Cast<ATMMAPlayerBase>(aPlayerPawn)) {
		if (PlayerCharacter->GetPlayerMode() == EPlayerMode::Shooting) return; //シューティングモードは固定の想定.
	}
	FVector PlayerLocation = aPlayerPawn->GetActorLocation();
	FVector CameraLocation = this->GetActorLocation();
	if ((PlayerLocation.Y - CameraLocation.Y) >= -100) {
		CameraPosition.Y = CameraVector.Y + PlayerLocation.Y;
	}
	if ((PlayerLocation.Z - CameraLocation.Z) >= 150) {
		CameraPosition.Z = PlayerLocation.Z - CameraVector.Z;
	} else 	if ((PlayerLocation.Z - CameraLocation.Z) <= -150) {
		CameraPosition.Z = PlayerLocation.Z + CameraVector.Z;
	}
}

void ATMMAPlayerCameraBase::MovingCameraYMighty()
{
	APawn* aPlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	FVector PlayerLocation = aPlayerPawn->GetActorLocation();
	FVector CameraLocation = this->GetActorLocation();
	CameraPosition.Y = CameraVector.Y + PlayerLocation.Y;
	if ((PlayerLocation.Z - CameraLocation.Z) >= 150) {
		CameraPosition.Z = PlayerLocation.Z - CameraVector.Z;
	}
	else if ((PlayerLocation.Z - CameraLocation.Z) <= -150) {
		CameraPosition.Z = PlayerLocation.Z + CameraVector.Z;
	}
}

void ATMMAPlayerCameraBase::MovingCameraZMighty()
{
	APawn* aPlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	FVector PlayerLocation = aPlayerPawn->GetActorLocation();
	FVector CameraLocation = this->GetActorLocation();
	if ((PlayerLocation.Y - CameraLocation.Y) >= -100) {
		CameraPosition.Y = CameraVector.Y + PlayerLocation.Y;
	}
	CameraPosition.Z = CameraVector.Z + PlayerLocation.Z;
}

void ATMMAPlayerCameraBase::MovingCameraYZMighty()
{
	APawn* aPlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	FVector PlayerLocation = aPlayerPawn->GetActorLocation();
	FVector CameraLocation = this->GetActorLocation();
	CameraPosition.Y = CameraVector.Y + PlayerLocation.Y;
	CameraPosition.Z = CameraVector.Z + PlayerLocation.Z;
}

void ATMMAPlayerCameraBase::LockCamera(AActor* InLockCollisionActor)
{
	CameraPosition = InLockCollisionActor->GetActorLocation() - FVector(300.0, 0.0, -20.0);
	// Y軸が動くことは現状想定していない.
	if (ZMightyFlag == true) {
		APawn* aPlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
		FVector PlayerLocation = aPlayerPawn->GetActorLocation();
		FVector CameraLocation = this->GetActorLocation();
		CameraPosition.Z = CameraVector.Z + PlayerLocation.Z;
	}
}

void ATMMAPlayerCameraBase::SetYMightyFlag(bool InYMightyFlag)
{
	YMightyFlag = InYMightyFlag;
}

void ATMMAPlayerCameraBase::SetZMightyFlag(bool InZMightyFlag)
{
	ZMightyFlag = InZMightyFlag;
}

void ATMMAPlayerCameraBase::InitCameraMightyFlag()
{
	YMightyFlag = false;
	ZMightyFlag = false;
}