// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"

ABulletBase::ABulletBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

//void ABulletBase::HitBulletByTarget(AActor* InHitActor)
//{
//	if ((InHitActor != nullptr) && (IsValid(InHitActor) == true)) {
//		if ((InHitActor->ActorHasTag("Enemy")) || (InHitActor->ActorHasTag("CrushObject"))) {
//			if (InHitActor->GetClass()->ImplementsInterface(TMMAEnemyActorBulletInterface))
//		}
//	}
//}

void ABulletBase::ReloadAndAddScore(bool IsNotDestroyBullet)
{
	if (PlayerBase != nullptr) {
		PlayerBase->ReloadBulletCount(BulletTableRow.ReloadBullet);
	}
	AddHitBulletScore();
	if (IsNotDestroyBullet == false) {
		Destroy();
	}
}

void ABulletBase::AddHitBulletScore()
{
	if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(MainGameState) == true) {
		MainGameState->AddP1Score(BulletTableRow.Score);
	}
}

void ABulletBase::SetDamageAndReloadPowerUp()
{
	if (PlayerBase != nullptr) {
		switch (PlayerBase->GetShotLevel()) 
		{
			case 2:
				BulletTableRow.Damage += BulletTableRow.AddedDamageParamLv2;
				if (BulletTableRow.ReloadBulletTimesLv2 > 0) {
					BulletTableRow.ReloadBullet *= BulletTableRow.ReloadBulletTimesLv2;
				}
				break;
			case 3:
				BulletTableRow.Damage += BulletTableRow.AddedDamageParamLv3;
				if (BulletTableRow.ReloadBulletTimesLv3 > 0) {
					BulletTableRow.ReloadBullet *= BulletTableRow.ReloadBulletTimesLv3;
				}
			default:
				break;
		}
	}
}

void ABulletBase::SetPlayerAndPowerStatus(ATMMAPlayerBase* InPlayerBase)
{
	SetPlayerBase(InPlayerBase);
	SetDamageAndReloadPowerUp();
}

void ABulletBase::PlayShotSoundPlay()
{
	if (IsValid(ShotSound)) {
		UGameplayStatics::PlaySound2D(this, ShotSound);
	}
}

void ABulletBase::SetShotSoundBySoft()
{
	ShotSound = SoftShotSound.LoadSynchronous();
}

void ABulletBase::SetSoftShotSoundAndPlay()
{
	ShotSound = SoftShotSound.LoadSynchronous();
	if (IsValid(ShotSound) == true) {
		UGameplayStatics::PlaySound2D(this, ShotSound);
	}
}


void ABulletBase::MovingBullet()
{
	LivingTime += 0.1;
	if (LivingTime >= BulletTableRow.DeleteTime) {
		LivingTime = 0.0;
		if (PlayerBase != nullptr) {
			PlayerBase->ReloadBulletCount(BulletTableRow.ReloadBullet);
		}
		Destroy();
	}
}

void ABulletBase::BeginPlay()
{
	// テーブルより各ステータス設定して、ついでにショット音も鳴らす.
//	SetBulletStatus(TableRowName);
	// データアセットより各ステータス設定して、ショット音を鳴らす.
	SetBulletStatusByAsset();
	PlayShotSoundPlay();
	// タイマー実行イベントの設定
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABulletBase::OnEventByTimer, 0.01f, true);
	Super::BeginPlay();
}

void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABulletBase::SetGameMode(ATestMyMakeActionGameModeBase* InGameMode)
{
	MainGameModeBase = InGameMode;
}

void ABulletBase::SetMainGameState(ATMMAGameStateBase* InMainGameState)
{
	MainGameState = InMainGameState;
}

void ABulletBase::SetPlayerBase(ATMMAPlayerBase* InPlayerBase)
{
	PlayerBase = InPlayerBase;
}

void ABulletBase::SetBulletStatus(FName InRowName)
{
	if (BulletDataTable != nullptr) {
		FBulletTableRow* BulletRecord = BulletDataTable->FindRow<FBulletTableRow>(InRowName, "");
		if (BulletRecord != nullptr) {
			BulletTableRow.Name = BulletRecord->Name;
			BulletTableRow.Damage = BulletRecord->Damage;
			BulletTableRow.AddedDamageParamLv2 = BulletRecord->AddedDamageParamLv2;
			BulletTableRow.AddedDamageParamLv3 = BulletRecord->AddedDamageParamLv3;
			BulletTableRow.DeleteTime = BulletRecord->DeleteTime;
			BulletTableRow.ReloadBulletTimesLv2 = BulletRecord->ReloadBulletTimesLv2;
			BulletTableRow.ReloadBulletTimesLv3 = BulletRecord->ReloadBulletTimesLv3;
			BulletTableRow.ReloadBullet = BulletRecord->ReloadBullet;
			BulletTableRow.Score = BulletRecord->Score;
			// パスが有効の時のみ、SE設定.
			TSoftObjectPtr<USoundBase> BulletSoundObj = LoadObject<USoundBase>(nullptr, (*BulletRecord->SoundPath), nullptr, LOAD_None, nullptr);
			if (BulletSoundObj != nullptr) {
				UE_LOG(LogTemp, Log, TEXT("BulletSoundObj Load Ok"));
				ShotSound = BulletSoundObj.LoadSynchronous();
				if (ShotSound != nullptr) {
					UE_LOG(LogTemp, Log, TEXT("ShotSound Set Ok"));
				}

			}
		}
	}
}

void ABulletBase::SetBulletStatusByAsset()
{
	BulletDataAsset = SoftBulletDataAsset.LoadSynchronous();
	if (BulletDataAsset != nullptr) {
		BulletTableRow.Damage = BulletDataAsset->GetDamage();
		BulletTableRow.AddedDamageParamLv2 = BulletDataAsset->GetAddedDamageParamLv2();
		BulletTableRow.AddedDamageParamLv3 = BulletDataAsset->GetAddedDamageParamLv3();
		BulletTableRow.ReloadBullet = BulletDataAsset->GetReloadBullet();
		BulletTableRow.ReloadBulletTimesLv2 = BulletDataAsset->GetReloadBulletTimesLv2();
		BulletTableRow.ReloadBulletTimesLv3 = BulletDataAsset->GetReloadBulletTimesLv3();
		BulletTableRow.DeleteTime = BulletDataAsset->GetDeleteTime();
		BulletTableRow.Score = BulletDataAsset->Score;
		// パスが有効の時のみ、SE設定.
		TSoftObjectPtr<USoundBase> SoftShotSoundByAsset = BulletDataAsset->GetSoftShotSound();
		ShotSound = SoftShotSoundByAsset.LoadSynchronous();
		if (ShotSound != nullptr) {
			UE_LOG(LogTemp, Log, TEXT("ShotSound Set Ok By DataAsset"));
		}
	}
}