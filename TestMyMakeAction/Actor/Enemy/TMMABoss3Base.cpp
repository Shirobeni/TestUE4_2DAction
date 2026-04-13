// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss3Base.h"
#include "Components/CapsuleComponent.h"

ATMMABoss3Base::ATMMABoss3Base()
{
	LanceComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LanceComponent"));
	SceneLanceComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneLanceComp"));
	if (LanceComponent) {
		LanceComponent->SetupAttachment(GetCapsuleComponent());
		LanceComponent->SetRelativeRotation(FRotator(100.0f, 0.0f, 0.0f));
		SceneLanceComp->SetupAttachment(LanceComponent);
	}
	BaseSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BaseSceneComponent"));
	USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (MeshComponent) {
		BaseSceneComponent->SetupAttachment(MeshComponent);
	}
}

void ATMMABoss3Base::BeginPlay()
{
	Super::BeginPlay();
	PatternCountChangeMod = 80;
	PatternCountEndCount = 240;
	LanceTimeCount = 0;
}

void ATMMABoss3Base::FunctionByTimerEvent()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
//	if (FVector::DistXY(PlayerLocation, GetActorLocation()) > 200) return;
	if (!WasRecentlyRendered(0.0)) return;
	if ((!GameMode) || (!GameMode->GetIsBossBattle())) return;
	if (!IsDefeated) {
		CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
		BossAttack();
		MoveLanceRotate();
		UE_LOG(LogTemp, Log, TEXT("PatternCount=%d"), PatternCount);
		UE_LOG(LogTemp, Log, TEXT("PatternTransform=%d"), PatternTransform);
		if(Hp < 10000 && TransformChangeOnceFlag == false){
			InitPatternStatus();
			PatternTransform = 2;
			TransformChangeOnceFlag = true;
		}
	}
}

void ATMMABoss3Base::BossAttack()
{
	switch (PatternTransform) {
		default:
			break;
		case 1:
			switch (PatternType) {
				default:
					break;
				case 0:
					if (PatternCount >= 10) {
						LanceAngleShot();
						LanceComponent->SetWorldLocation(BaseSceneComponent->GetComponentLocation());
					}
					break;
				case 1:
					LanceAttack();
					break;
				case 2:
					if (PatternCount >= 10) {
						ShotDelayFloat = 0.2f;
						ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
							SpreadShot();
						});
					}
					break;
			}
			break;
		case 2:
			switch (PatternType) {
				default:
					break;
				case 0:
					ShotDelayFloat = 0.2f;
					ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
						SpredShotByPt2();
					});
					break;
				case 1:
					LanceComponent->AddWorldOffset(FVector(0.0f, -10.0f, 0.0f));
					break;
				case 2:
					LanceComponent->AddWorldOffset(FVector(0.0f, 10.0f, 0.0f));
					break;
			}
			break;
	}
}

void ATMMABoss3Base:: MoveLanceRotate()
{
	if(PatternTransform == 2 && PatternType != 0) {
		LanceComponent->AddWorldRotation(FRotator(0.0f, 0.0f, 30.0f));
	} else {
		FVector PlayerLocation;
		UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
		FVector LanceLocation = LanceComponent->GetComponentLocation();
		FRotator LanceRotator = UKismetMathLibrary::FindLookAtRotation(LanceLocation, PlayerLocation);
		LanceRotator.Pitch -= 85.0;
		LanceComponent->SetWorldRotation(LanceRotator);
	}
}

void ATMMABoss3Base::LanceAngleShot()
{
	InVector = FVector(0.0f, 1.0f, 0.0f);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector SceneLanceLocation = SceneLanceComp->GetComponentLocation(); 
	float AddPitchRotate = (PatternCount / 10) * 30.0f;
	AActor* SpawnShot;
	ShotEnemyBulletXVectorForVectorByCombineByIndex(BulletSetVec, SceneLanceLocation, InVector, 0, FVector(0.7f, 0.7f, 0.5f), FRotator(AddPitchRotate, 0.0, 0.0f), SpawnShot);
}

void ATMMABoss3Base::LanceAttack()
{
	LanceTimeCount++;
	FVector AddLanceVect = LanceComponent->GetComponentLocation();
	if (LanceTimeCount > 40) {
		LanceTimeCount = 0;
	}
	else if (LanceTimeCount > 10) {
		AddLanceVect.Y += 10.0f;
		LanceComponent->SetWorldLocation(AddLanceVect);
	}
	else if (LanceTimeCount > 0) {
		AddLanceVect.Y -= 30.0f;
		LanceComponent->SetWorldLocation(AddLanceVect);
	}
}

void ATMMABoss3Base::SpreadShot()
{
	InVector = FVector(0.0f, -1.0f, -1.0f);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector LanceSceneVec = SceneLanceComp->GetComponentLocation();
	float AddPitchRotate = (PatternCount * 10) * 30.0f;
	AActor* SpawnShot;
	ShotEnemyBulletXVectorForVectorByCombineByIndex(BulletSetVec, LanceSceneVec, InVector, 1, FVector(0.7f, 0.7f, 0.5f), FRotator(0.0f, AddPitchRotate, 0.0f), SpawnShot);
}

void ATMMABoss3Base::SpredShotByPt2()
{
	InVector = FVector(0.0f, -3.0f, -1.0f);
	FVector BulletSetVec = FVector(0.0f, 0.0f, 0.0f);
	FVector LanceSceneVec = SceneLanceComp->GetComponentLocation();
	float AddPitchRotate = UKismetMathLibrary::RandomFloatInRange(0.0f, 120.0f);
	AActor* SpawnShot;
	ShotEnemyBulletXVectorForVectorByCombineByIndex(BulletSetVec, LanceSceneVec, InVector, 1, FVector(0.7f, 0.7f, 0.5f), FRotator(0.0f, AddPitchRotate, 0.0f), SpawnShot);
	if (!SpawnShot) return;
	if (ATMMAEnemyBulletBase* CastedSpawnShot = Cast<ATMMAEnemyBulletBase>(SpawnShot)) {
		CastedSpawnShot->GetProjectileMovement()->Velocity *= UKismetMathLibrary::RandomFloatInRange(10.f, 4.0f);
	}
}