// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMACameraMightyCollisionBase.h"

// Sets default values
ATMMACameraMightyCollisionBase::ATMMACameraMightyCollisionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMMACameraMightyCollisionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMMACameraMightyCollisionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMMACameraMightyCollisionBase::SetPlayerCamera(ATMMAPlayerCameraBase* InPlayerCamera)
{
	PlayerCamera = InPlayerCamera;
}

void ATMMACameraMightyCollisionBase::SwitchMighty()
{
	if (PlayerCamera != nullptr) {
		switch (MightyStatus) {
			case EMightyType::YOnly:
				PlayerCamera->SetYMightyFlag(true);
				PlayerCamera->SetZMightyFlag(false);
				break;
			case EMightyType::ZOnly:
				PlayerCamera->SetYMightyFlag(false);
				PlayerCamera->SetZMightyFlag(true);
				break;
			case EMightyType::YAndZ:
				PlayerCamera->SetYMightyFlag(true);
				PlayerCamera->SetZMightyFlag(true);
				break;
			default:
				PlayerCamera->SetYMightyFlag(false);
				PlayerCamera->SetZMightyFlag(false);
				break;
		}
	}
}

