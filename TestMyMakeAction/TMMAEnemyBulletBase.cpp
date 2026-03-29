// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAEnemyBulletBase.h"

// Sets default values
ATMMAEnemyBulletBase::ATMMAEnemyBulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void ATMMAEnemyBulletBase::BeginPlay()
{
	PlayShotSound();
	Super::BeginPlay();
	
}

// Called every frame
void ATMMAEnemyBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 弾を動かす
void ATMMAEnemyBulletBase::MovingBullet(float AddTime, float InLivingTime)
{
	// 何も設定しない(0.0のまま)か0より小さい値ならLimitTimeを設定する.
	if (InLivingTime <= 0.0) {
		InLivingTime = LimitTime;
	}
	LivingTime += AddTime;
	if (LivingTime > InLivingTime) {
		LivingTime = 0.0;
		Destroy();
	}
}

void ATMMAEnemyBulletBase::SetBulletLivingTime(float InLivingTime)
{
	LivingTime = InLivingTime;
}

void ATMMAEnemyBulletBase::SetBulletLimitTime(float InLimitTime)
{
	LimitTime = InLimitTime;
}

bool ATMMAEnemyBulletBase::SetEnemyBulletStatus(FName SetRowName, FEnemyBulletTableRow& EnemyBulletParam)
{
	if (DataTable != nullptr) {
		FEnemyBulletTableRow* EnemyBulletRecord = DataTable->FindRow<FEnemyBulletTableRow>(SetRowName, "");
		if (EnemyBulletRecord != nullptr) {
			Damage = EnemyBulletRecord->DamageParam;
			LimitTime = EnemyBulletRecord->LimitTime;
			// サウンドパスがあるならサウンド生成.
			TSoftObjectPtr<USoundBase> SoftBulletSound = LoadObject<USoundBase>(nullptr, (*EnemyBulletRecord->SoundPath), nullptr, LOAD_None, nullptr);
			if (SoftBulletSound != nullptr) {
				ShotSound = SoftBulletSound.LoadSynchronous();
			}
// TODO:: いらないと分かれば削除.
//			SetBulletDestroyTime(EnemyBulletParam.DestroyTime);
			return true;
		}
	}
	return false;
}

// 自由に弾速を設定
void ATMMAEnemyBulletBase::SetBulletSpeed(float VectorMul)
{
	if (BulletProjectileMovement != nullptr) {
		BulletProjectileMovement->Velocity = BulletProjectileMovement->Velocity * VectorMul;
	}
}

// ランクに応じて弾速を変化
void ATMMAEnemyBulletBase::SetBulletSpeedOnRank(int Rank)
{
	if (BulletProjectileMovement != nullptr) {
		BulletProjectileMovement->Velocity = BulletProjectileMovement->Velocity * (1 + (float(Rank) * 0.05));
	}
}

void ATMMAEnemyBulletBase::SetBulletLife(int InLife)
{
	BulletLife = InLife;
}

void ATMMAEnemyBulletBase::AddBulletLife(int AddLife)
{
	BulletLife -= AddLife;
	//	if (BulletLife < 1) {
	//		Destroy();
	//	}
}

// サウンド再生
void ATMMAEnemyBulletBase::PlayShotSound()
{
	if (IsValid(ShotSound)) {
		UGameplayStatics::PlaySound2D(GetWorld(), ShotSound);
	}
}



