// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss2Base.h"
#include "Components/CapsuleComponent.h"


void ATMMABoss2Base::BeginPlay()
{
	Super::BeginPlay();
	PatternCountChangeMod = 30;
	PatternCountEndCount = 90;
	// AI移動用のロック用アクタの設定.
	TSubclassOf<ATMMALockCollisionBase> BossLockCollisionClass = SofBossLockCollisionClass.LoadSynchronous();
	if (!BossLockCollisionClass) return;
	AActor* GettedLockCollision = UGameplayStatics::GetActorOfClass(GetWorld(), BossLockCollisionClass);
	if (!GettedLockCollision) return;
	if (ATMMALockCollisionBase* CastedBossLockCollision = Cast<ATMMALockCollisionBase>(GettedLockCollision)) {
		BossLockCollision = CastedBossLockCollision;
	}
}

void ATMMABoss2Base::FunctionByTimerEvent()
{
	if (!WasRecentlyRendered(0.0)) return;
	if (!GameMode) return;
	if (!IsDefeated) {
		CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
		BossAction();
		ChangeTransform();
	}
}

void ATMMABoss2Base::BossAction()
{
	switch (PatternTransform) {
		default:
			break;
		case 1:
			switch (PatternType) {
				default:
					break;
				case 0:
					ShotDelayFloat = 1.0f;
					ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
						AimShotByLeg();
					});
//					GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss2Base::AimShotByLeg, 1.0, false);
					break;
				case 1:
					if (SpawnActorClassList[0]) {
						FTransform Transform = UKismetMathLibrary::MakeTransform(GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
						GetWorld()->SpawnActor<AActor>(SpawnActorClassList[0], Transform);
					}
					break;
				case 2:
					ShotLaser();
					break;
			}
			break;
		case 2:
			FTransform Transform = UKismetMathLibrary::MakeTransform(GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
			ShotDelayFloat = 1.0f;
			ShotDelayFunction(&ShotFloat, ShotDelayFloat, [this]() {
				AimShotByLeg();
			});
//			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATMMABoss2Base::AimShotByLeg, 1.0, false);
			break;

	}
}

void ATMMABoss2Base::ChangeTransform()
{
	if (Hp < 1500 && IsTransformChangeDoOnce == false) {
		PatternTransform = 2;
		UTMMAActorLibrary::SpawnSeAndParticleBySoft(this, TransformParticle, TransformSound, GetActorLocation(), FVector(1.0f, 1.0f, 1.0f));
		MoveGround();
	}
}

void ATMMABoss2Base::SetLegCannonComponents(TArray<USceneComponent*> InLegCannonComponents)
{
	LegCannonComponents = InLegCannonComponents;
}

void ATMMABoss2Base::MoveGround()
{
	SetActorRotation(FRotator(-90.0f, 0.0f,0.0f));
	GetCapsuleComponent()->SetEnableGravity(true);
}

void ATMMABoss2Base::AimShotByLeg()
{
	USceneComponent* PlayerCapsuleComponent = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCapsuleComponent();
	if (!PlayerCapsuleComponent) return;
	for (USceneComponent* LegCannonComponent : LegCannonComponents) {
		FTransform Transform;
		UTMMAActorLibrary::GetAimTransformComponent(FVector(0.0f, 0.0f, 0.0f), LegCannonComponent, PlayerCapsuleComponent, FVector(0.5, 0.5, 0.3), Transform);
		AActor* SpawnShot = GetWorld()->SpawnActor<AActor>(ShotEnemyBulletList[0], Transform);
		if (IsValid(SpawnShot)) {
			AddSpawnActorList(SpawnShot);
		}
	}
}

void ATMMABoss2Base::ShotLaser()
{
	FVector StartVector = GetActorLocation();
	StartVector.Y -= 150.0f;
	FTransform Transform;
	UTMMAActorLibrary::GetAimTransformForVector(FVector(0.0f, 0.0f, 0.0f), StartVector, FVector(0.0f, 0.0f, 0.0f), FVector(0.5f, 0.5f, 0.5f), Transform);
	AActor* SpawnLaser = GetWorld()->SpawnActor<AActor>(ShotEnemyBulletList[1], Transform);
	if (IsValid(SpawnLaser)) {
		SpawnLaser->AddActorWorldRotation(FRotator(90.0f, 0.0f, 0.0f));
	}
}


