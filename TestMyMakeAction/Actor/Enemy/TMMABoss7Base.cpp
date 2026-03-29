
// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMABoss7Base.h"
#include "Components/CapsuleComponent.h"
#include "TestMyMakeAction/AI/TMMABoss7AiBase.h"

ATMMABoss7Base::ATMMABoss7Base()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ATMMABoss7Base::BeginPlay()
{
	Super::BeginPlay();
	IsWait = false;
	SetPatrollPoint();
	ThunderParticle = SoftThunderParticle.LoadSynchronous();
}

void ATMMABoss7Base::FunctionByTimerEvent()
{
	// TODO::一旦準備が出来てから解除
   if (WasRecentlyRendered(0.2) && GameMode->GetIsBossBattle() == true) {
  		CountingPatternCoundGrandBoss7();
		// パターンに応じた攻撃
		switch (PatternTransform) 
		{
			case 1:
				BossTransform1();
				break;
			case 2:
				BossTransform2();
				break;
			case 3:
				BossTransform3();
				break;
			case 4:
				BossTransform4();
				break;
			default:
				break;
		}
		TransformChange();
   }
}

// 一部パターンの移動先設定
void ATMMABoss7Base::SetPatrollPoint()
{
	// 一旦nullチェックを入れるようにする
	ATMMAEnemyPatrollPoint* LoadPatrollPoint1 = SoftPatrollPoint1.LoadSynchronous();
	if (LoadPatrollPoint1 != nullptr) {
		PatrollPoint1 = LoadPatrollPoint1;
	}
	int SoftPatrollPoint2ListNum = SoftPatrollPoint2List.Num();
	if (SoftPatrollPoint2ListNum >= 1) {
		for (TSoftObjectPtr<ATMMAEnemyPatrollPoint> SoftPatrollPoint2 : SoftPatrollPoint2List) {
			ATMMAEnemyPatrollPoint* LoadPatrollPoint2 = SoftPatrollPoint2.LoadSynchronous();
			if (LoadPatrollPoint2 != nullptr) {
				PatrollPoint2List.Add(LoadPatrollPoint2);
			}
		}
	}
}

void ATMMABoss7Base::CountingPatternCoundGrandBoss7() 
{
	if(IsWait == false)
	{
		PatternCountChangeMod = 30;
		PatternCountEndCount = 360;
		switch(PatternTransform){
			case 2:
				PatternCountChangeMod = 80;
				PatternCountEndCount = 400;
				break;
			case 3:
				PatternCountChangeMod = 90;
				PatternCountEndCount = 450;
				break;
			default:
				break;
		}
		CountingPatternCount(PatternCountChangeMod, PatternCountEndCount);
	}
}

// 形態変化
void ATMMABoss7Base::TransformChange()
{
	bool TransformFlag = false;
	if (Hp <= 49000 && PatternTransform == 1) {
		PatternTransform = 2;
		TransformFlag = true;
	}
	else if (Hp <= 21000 && PatternTransform == 2) {
		PatternTransform = 3;
		TransformFlag = true;
	}
	else if (Hp <= 7000 && PatternTransform == 3) {
		USceneComponent* PlayerComponent = NewObject<USceneComponent>(UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0));
		ProjectileMovementComponent->HomingTargetComponent = PlayerComponent;
		ProjectileMovementComponent->bIsHomingProjectile = true;
		ProjectileMovementComponent->InitialSpeed = 50.0;
		PatternTransform = 4;
		// 引っかかるの防止？でコリジョンオフ
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TransformFlag = true;
	}
	if (TransformFlag) {
		PatternCount = 0;
		SpawnDefeatedPerticleAndSe(DefeatParticleObj, DefeatSoundObj, FVector(10.0f, 10.0f, 10.0f));
	}
}

// 攻撃準備フラグの設定
void ATMMABoss7Base::SetIsWait(bool InIsWait)
{
	IsWait = InIsWait;
}

// 第一形態攻撃
void ATMMABoss7Base::BossTransform1()
{
	switch (PatternType) {
		case 1:
			IsHomingLaserDoOnce = false; // パターン4用のDoOnceフラグをここで一旦falseにする.
			ShotLaserAndMove();
			break;
		case 2:
		case 3:
			// SetTimer多重実行防止でIsTimerActive判定.
			FirstShotDelayFloat = 0.4f;
			ShotDelayFunction(&FirstShotFloat, FirstShotDelayFloat, [this]() {
				ShotDestroyHoming();
			});
//			if (!GetWorld()->GetTimerManager().IsTimerActive(Handle)) {
//				GetWorld()->GetTimerManager().SetTimer(Handle, this, &ATMMABoss7Base::ShotDestroyHoming, 0.4f, false);
			break;
		case 4:
			if (!IsHomingLaserDoOnce) {
				FVector PlayerLocation;
				UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
				AActor* SpawnHomingLaser;
				ShotEnemyBulletAimByIndex(FVector(0.0f, 0.0f, 0.0f), PlayerLocation, 2, FVector(0.5f, 0.5f, 0.5f), SpawnHomingLaser);
				IsHomingLaserDoOnce = true;
			}
			break;
		case 5:
//			GetWorld()->GetTimerManager().ClearTimer(Handle);
			if (PatternTransform == 1) {
				UTMMAActorLibrary::MoveActorToTarget(this, PatrollPoint1, 10.0f);
			}
		default:
			break;
	}
}

// 第二形態
void ATMMABoss7Base::BossTransform2()
{
	// 一度だけ初期位置へ移動する.
	if (!IsMoveToPtPoint2DoOnce) {
		IsWait = true;
		if (IsValid(PatrollPoint2List[0])) {
			if (!Controller) return;
			if (AAIController* AIController = Cast<AAIController>(Controller)) {
				if (ATMMABoss7AiBase* Boss7Ai = Cast<ATMMABoss7AiBase>(AIController)) {
					Boss7Ai->MoveToActor(PatrollPoint2List[0]);
					IsMoveToPtPoint2DoOnce = true;
				}
			}
		}
	}
	if (IsWait) return;
	// パターンタイプに応じた挙動
	switch (PatternType) {
		case 1:
			if (!IsJumpAndSpawnDoOnce) {
				// ショット射出メソッドだけど…敵を生成(後々敵用の生成メソッドを作りたい)
				FVector PlayerLocation;
				FVector ScaleVector = FVector(0.5f, 0.5f, 0.5f);
				UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
				ShotEnemyWayBulletAim(FVector(0.0f, 0.0f, 0.0f), PlayerLocation, ScaleVector, 3, 60.0f, SpawnActorClassList[0]);
				IsJumpAndSpawnDoOnce = true;
			}
			break;
		case 2:
			JumpKick();
			break;
		case 3:
			if (!IsForceBulletSpawnDoOnce) {
				FirstShotDelayFloat = 1.0f;
				ShotDelayFunction(&FirstShotFloat, FirstShotDelayFloat, [this]() {
					SpawnForceBullet();
				});
			}
			break;
		case 4:
			// 各DoOnceフラグをfalseに設定
			IsJumpAndSpawnDoOnce = false;
			IsForceBulletSpawnDoOnce = false;
			if (IsValid(PatrollPoint2List[0])) {
				UTMMAActorLibrary::MoveActorToTarget(this, PatrollPoint2List[0], 10.0f);
			}

	}
}

// 第三形態
void ATMMABoss7Base::BossTransform3()
{
	//
	if (!IsMoveToPtPoint1DoOnce) {
		IsWait = true; // 移動中に攻撃を行わないようにする.
//		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
//		GetCharacterMovement()->GravityScale = 0.0f;
		if (IsValid(PatrollPoint1)) { // 移動先ポイントアクタが設定されていなければ処理を行わない.return;
			UTMMAActorLibrary::MoveActorToTarget(this, PatrollPoint1, 10.0f);
			if (FVector::Dist(GetActorLocation(), PatrollPoint1->GetActorLocation()) < 10.0f) {
				SetActorLocation(PatrollPoint1->GetActorLocation());
				IsMoveToPtPoint1DoOnce = true;
				IsWait = false;
			}
//			if (!Controller) return; // コントローラーも取得できなかったら行わない.
//			if (AAIController* AIController = Cast<AAIController>(Controller)) {
//				if (ATMMABoss7AiBase* Boss7Ai = Cast<ATMMABoss7AiBase>(AIController)) {
//					Boss7Ai->MoveToActor(PatrollPoint1);
//					IsMoveToPtPoint1DoOnce = true;
//				}
//			}
		}
	}

	if (IsWait) return;
	switch (PatternType) {
		case 1:
			IsSpawnThunderLaserDoOnce = false;
			FirstShotDelayFloat = 0.2f;
			ShotDelayFunction(&FirstShotFloat, FirstShotDelayFloat, [this]() {
				SpawnDestroyShot();
			});
			break;
		case 2:
			FirstShotDelayFloat = 0.4f;
			ShotDelayFunction(&FirstShotFloat, FirstShotDelayFloat, [this]() {
				SpawnThunderShot();
			});
			break;
		case 3:
			FirstShotDelayFloat = 0.2f;
			ShotDelayFunction(&FirstShotFloat, FirstShotDelayFloat, [this]() {
				SpawnThunderShot();
			});
			break;
		case 4:
			SpawnThunderParticle();
			break;
		case 5:
			IsSpawnLaserParticleDoOnce = false;
			SpawnThunderLaser();
			break;
	}
}

// 第四形態
void ATMMABoss7Base::BossTransform4()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn)) {
		UTMMAActorLibrary::MoveActorToTarget(this, PlayerPawn, 1.0f);
	}
	FirstShotDelayFloat = 0.5f;
	ShotDelayFunction(&FirstShotFloat, FirstShotDelayFloat, [this]() {
		SpawnEnemyBullet();
	});
	SecondShotDelayFloat = 1.0f;
	ShotDelayFunction(& SecondShotFloat, SecondShotDelayFloat, [this]() {
		SpawnEnemyHomingMissile();
	});
	ThirdShotDelayFloat = 2.0f;
	ShotDelayFunction(& ThirdShotFloat, ThirdShotDelayFloat, [this]() {
		SpawnEnemyFire();
	});
}

// レーザー発射しながら移動
void ATMMABoss7Base::ShotLaserAndMove()
{
	// キャラの移動
	FVector InMoveVector = FVector(0.0f, -10.0f, 0.0f);
	if (GetDistanceAtPlayer().Y >= 0.0) {
		InMoveVector.Y = 10.0f;
	}
	MoveEnemy(InMoveVector);
	// レーザー発射
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	AActor* SpawnLaser;
	ShotEnemyBulletAimByIndex(FVector(0.0f, 0.0f, 0.0f), PlayerLocation, 0, FVector(0.3f, 0.3f, 0.5f), SpawnLaser);
	if (IsValid(SpawnLaser)) {
		SpawnLaser->AddActorLocalRotation(FRotator(0.0f, 90.0f, 0.0f));
	}
}

// 破壊可能ホーミング弾発射 ※タイマー管理で呼び出すため.
void ATMMABoss7Base::ShotDestroyHoming()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	AActor* SpawnDestroyHoming;
	ShotEnemyBulletAimByIndex(FVector(0.0f, 0.0f, 0.0f), PlayerLocation, 1, FVector(0.3f, 0.3f, 0.5f), SpawnDestroyHoming);
}

// ジャンプキック攻撃
void ATMMABoss7Base::JumpKick()
{
	if (PatternCount >= 180) {
		MoveEnemy(FVector(0.0f, -9.0f, -5.0f));
	}
	else {
		MoveEnemy(FVector(0.0f, -3.0f, 15.0f));
	}
}

// 高速波動弾発射
void ATMMABoss7Base::SpawnForceBullet()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	AActor* SpawnedForceBullet;
	ShotEnemyBulletAimByIndex(FVector(0.0f, 0.0f, 0.0f), PlayerLocation, 3, FVector(0.3f, 0.3f, 0.5f), SpawnedForceBullet);
	IsForceBulletSpawnDoOnce = true;
}

// 破壊可能弾発射※タイマー管理で呼び出すため.
void ATMMABoss7Base::SpawnDestroyShot()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	ShotEnemyWayBulletAimByIndex(FVector(0.0f, 0.0f, 0.0f), PlayerLocation, FVector(0.3f, 0.3f, 0.5f), 5, 10.0f, 4);
}

void ATMMABoss7Base::SpawnThunderShot()
{
	// 開始位置用プレイヤーロケーション
	FVector StartPlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(StartPlayerLocation);
	StartPlayerLocation.Y += (UKismetMathLibrary::RandomFloatInRange(-50.0f, 50.0f) * 5);
	StartPlayerLocation.Z += 300.0f;
	// ターゲット用プレイヤーロケーション
	FVector TargetPlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(TargetPlayerLocation);
	FTransform ShotTransform;
	UTMMAActorLibrary::GetAimTransformForVector(FVector(0.0f, 0.0f, 0.0f), StartPlayerLocation, TargetPlayerLocation, FVector(0.3f, 0.3f, 0.3f), ShotTransform);
	ShotTransform.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	GetWorld()->SpawnActor<AActor>(ShotEnemyBulletList[5], ShotTransform);
}

// サンダーレーザー前のパーティクル生成
void ATMMABoss7Base::SpawnThunderParticle() {
	if (!IsSpawnLaserParticleDoOnce && ThunderParticle != nullptr) {
		for (int i = 0; i < 5; i++) {
			FVector StartPlayerLocation;
			UTMMAActorLibrary::GetPlayerLocation(StartPlayerLocation);
			StartPlayerLocation.Y += (UKismetMathLibrary::RandomFloatInRange(-50.0f, 50.0f) * 10);
			StartPlayerLocation.Z = 50.0f;
			FVector TargetPlayerLocation;
			UTMMAActorLibrary::GetPlayerLocation(TargetPlayerLocation);
			FTransform ShotTransform;
			UTMMAActorLibrary::GetAimTransformForVector(FVector(0.0f, 0.0f, 0.0f), StartPlayerLocation, TargetPlayerLocation, FVector(0.3f, 0.3f, 0.3f), ShotTransform);
			ShotTransform.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
			UParticleSystemComponent* ThunderParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ThunderParticle, ShotTransform);
			if (IsValid(ThunderParticleComponent)) {
				LaserParticleList.Add(ThunderParticleComponent);
				FVector LaserVector = ThunderParticleComponent->GetComponentLocation();
				// パーティクルの位置にレーザーを出すためのベクトル一覧
				LaserVector.Z = 50.0f;
				LaserVectorList.Add(LaserVector);
			}
		}
	}
	IsSpawnLaserParticleDoOnce = true;
}

void ATMMABoss7Base::SpawnThunderLaser()
{
	if (!IsSpawnThunderLaserDoOnce) {
		for (int i = 0; i < 5; i++) {
			FTransform ShotTransform = UKismetMathLibrary::MakeTransform(LaserVectorList[i], FRotator(0.0f, 0.0f, 0.0f), FVector(0.1f, 0.1f, 4.0f));
			GetWorld()->SpawnActor<AActor>(ShotEnemyBulletList[6], ShotTransform);
			LaserVectorList.Remove(LaserVectorList[i]);
			LaserParticleList[i]->DestroyComponent();
		}
		IsSpawnThunderLaserDoOnce = true;
	}
}

void ATMMABoss7Base::SpawnEnemyBullet()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	ShotEnemyWayBulletAimByIndex(FVector(0.0f, 0.0f, 0.0f), PlayerLocation, FVector(0.3, 0.3, 0.3), 3, 10.0, 7);
}

void ATMMABoss7Base::SpawnEnemyHomingMissile()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	ShotEnemyWayBulletAimByIndex(FVector(0.0f, 0.0f, 0.0f), PlayerLocation, FVector(0.05f, 0.05f, 0.05f), 3, 10.0, 8);
}

void ATMMABoss7Base::SpawnEnemyFire()
{
	FVector PlayerLocation;
	UTMMAActorLibrary::GetPlayerLocation(PlayerLocation);
	AActor* SpawnFire;
	ShotEnemyBulletAimByIndex(FVector(0.0f, 0.0f, 0.0f), PlayerLocation, 9, FVector(0.05f, 0.05f, 0.05f), SpawnFire);
}
