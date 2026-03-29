// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAItemBase.h"
#include "TestMyMakeAction/GameState/TMMAGameStateBase.h"
#include "TestMyMakeAction/Interface/TMMAGameStateInterface.h"

// Sets default values
ATMMAItemBase::ATMMAItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATMMAItemBase::SetStatusByTable(FName TableRow)
{
	if (ItemDataTable != nullptr) {
		FItemTableRow* ItemTableRecord = ItemDataTable->FindRow<FItemTableRow>(TableRow, "");
		if (ItemTableRecord != nullptr) {
			ItemName = ItemTableRecord->ItemName;
			ItemCategoryName = ItemTableRecord->ItemCategoryName;
			WeaponCategory = ItemTableRecord->ChangeWeapon;
			TSoftObjectPtr<USoundBase> GetSoundObj = LoadObject<USoundBase>(nullptr, (*ItemTableRecord->SoundPath), nullptr, LOAD_None, nullptr);
			if (GetSoundObj != nullptr) {
				UE_LOG(LogTemp, Log, TEXT("Get Sound Obj Load Ok"));
				GetItemSound = GetSoundObj.LoadSynchronous();
				if (GetItemSound != nullptr) {
					UE_LOG(LogTemp, Log, TEXT("Get Item Sound Set Ok"));
				}
			}
		}
	}
}

void ATMMAItemBase::SetStatusByAsset()
{
	ItemDataAsset = SoftItemDataAsset.LoadSynchronous();
	if (ItemDataAsset != nullptr) {
		// アイテムの種類 ※デフォルトはパワーアップ
		switch (ItemDataAsset->GetItemType()) {
			case EAssetItemType::ChangeRapid:
				ItemType = EItemType::ChangeRapid;
				break;
			case EAssetItemType::ChangeHoming:
				ItemType = EItemType::ChangeHoming;
				break;
			case EAssetItemType::ChangeFire:
				ItemType = EItemType::ChangeFire;
				break;
			case EAssetItemType::ChangeGrenade:
				ItemType = EItemType::ChangeGrenade;
				break;
			case EAssetItemType::ChangeLaser:
				ItemType = EItemType::ChangeLaser;
				break;
			case EAssetItemType::GetBurst:
				ItemType = EItemType::GetBurst;
				break;
			case EAssetItemType::LifeUp:
				ItemType = EItemType::LifeUp;
			default:
				ItemType = EItemType::PowerUp;
		}
		// 武器チェンジ種類
		switch (ItemDataAsset->GetChangeWeaponType()){
			case EAssetChangeWeaponType::Rapid:
				ChangeWeaponType = EChangeWeaponType::Rapid;
				break;
			case EAssetChangeWeaponType::Homing:
				ChangeWeaponType = EChangeWeaponType::Homing;
				break;
			case EAssetChangeWeaponType::Fire:
				ChangeWeaponType = EChangeWeaponType::Fire;
				break;
			case EAssetChangeWeaponType::Grenade:
				ChangeWeaponType = EChangeWeaponType::Grenade;
				break;
			case EAssetChangeWeaponType::Laser:
				ChangeWeaponType = EChangeWeaponType::Laser;
				break;
			default:
				ChangeWeaponType = EChangeWeaponType::None;
				break;
		}
		GetItemSound = ItemDataAsset->GetSoftGettedSound().LoadSynchronous();
		if (GetItemSound != nullptr) {
			UE_LOG(LogTemp, Log, TEXT("Get Item Sound Set By Asset Ok"));
		}
		BoxMaterial = ItemDataAsset->GetSoftBoxMaterial().LoadSynchronous();
		IconCharMesh = ItemDataAsset->GetSoftIconCharMesh().LoadSynchronous();
		AddLocationParamForChar = ItemDataAsset->GetAssetAddLocationParamForChar();
		AddRotationParamForChar = ItemDataAsset->GetAssetAddRotationParamForChar();
		ScaleVectorForChar = ItemDataAsset->GetAssetScaleVectorForChar();
	}
}

void ATMMAItemBase::PlayItemGetSound()
{
	if (IsValid(GetItemSound)) {
		UGameplayStatics::PlaySound2D(GetWorld(), GetItemSound);
	}
}

void ATMMAItemBase::ItemGet(AActor* InPlayerActor, AActor* InGetItemActor)
{
	if (ATMMAPlayerBase* PlayerActor = Cast<ATMMAPlayerBase>(InPlayerActor)) {
		if (ATMMAGetItemActor* GetItemActor = Cast<ATMMAGetItemActor>(InGetItemActor)) {
			int ShotLevel = PlayerActor->GetShotLevel();
			switch (ItemDataAsset->GetItemType()) {
				// デフォルトはパワーアップで
				default:
					PlayerPowerUp(PlayerActor, GetItemActor);
					break;
				case EAssetItemType::ChangeRapid:
				case EAssetItemType::ChangeHoming:
				case EAssetItemType::ChangeFire:
				case EAssetItemType::ChangeGrenade:
				case EAssetItemType::ChangeLaser:
					ChangeWeapon(PlayerActor, GetItemActor);
					break;
				case EAssetItemType::GetBurst:
					AddBurst(PlayerActor, GetItemActor);
				case EAssetItemType::LifeUp:
					AddPlayerLife(PlayerActor, GetItemActor);
			}
			PlayItemGetSound();
		}
	}
}

// パワーアップアイテム取得処理
void ATMMAItemBase::PlayerPowerUp(ATMMAPlayerBase* InPlayerActor, ATMMAGetItemActor* InGetItemActor)
{
	int ShotLevel = InPlayerActor->GetShotLevel();
	if (ShotLevel == 3) {
		AGameStateBase* GameStateBase = GetWorld()->GetGameState();
		IGameStateInterface::Execute_AddItemScore(GameStateBase, 1000);
	}
	else {
		InPlayerActor->ShotLevelUp();
	}
	InGetItemActor->SetItemTypeAndText(EGetItemType::PowerUp, ShotLevel);
}

// 武器チェンジ処理
void ATMMAItemBase::ChangeWeapon(ATMMAPlayerBase* InPlayerActor, ATMMAGetItemActor* InGetItemActor)
{
	if (IsValid(ItemDataAsset)) {
		EShotType SelectShotType = EShotType::Rapid;
		EGetItemType SelectGetItemType = EGetItemType::Rapid;
		switch (ItemDataAsset->GetItemType()) {
			default:
				break;
			case EAssetItemType::ChangeHoming :
				SelectShotType = EShotType::Homing;
				SelectGetItemType = EGetItemType::Homing;
				break;
			case EAssetItemType::ChangeFire:
				SelectShotType = EShotType::Fire;
				SelectGetItemType = EGetItemType::Fire;
				break;
			case EAssetItemType::ChangeGrenade:
				SelectShotType = EShotType::Grenade;
				SelectGetItemType = EGetItemType::Grenade;
				break;
			case EAssetItemType::ChangeLaser:
				SelectShotType = EShotType::Laser;
				SelectGetItemType = EGetItemType::Laser;
				break;
		}
		InPlayerActor->SetShotType(SelectShotType);
		InGetItemActor->SetItemTypeAndText(SelectGetItemType, 0);
 	}
}

// バーストアイテム取得処理
void ATMMAItemBase::AddBurst(ATMMAPlayerBase* InPlayerActor, ATMMAGetItemActor* InGetItemActor)
{
	InPlayerActor->AddBurstCount();
	InGetItemActor->SetItemTypeAndText(EGetItemType::Burst, 0);
}

void ATMMAItemBase::AddPlayerLife(ATMMAPlayerBase* InPlayerActor, ATMMAGetItemActor* InGetItemActor)
{
	if (InPlayerActor->GetPlayerLife() > 150) {
		InPlayerActor->SetPlayerLife(150);
	}
	else {
		InPlayerActor->AddPlayerLife(20);
	}
	InGetItemActor->SetItemTypeAndText(EGetItemType::Life, 0);
}

// Called when the	game starts or when spawned
void ATMMAItemBase::BeginPlay()
{
	// 現在のレベル名を取得。
	CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	Super::BeginPlay();
	
}

// Called every frame
void ATMMAItemBase::Tick(float DeltaTime)
{
	// 現在のレベルがステージ5ならアクタを左側へ移動(※stage5はシューティングステージになる)
	if (CurrentLevelName ==  FString::Printf(TEXT("stage5"))) {
		this->AddActorLocalOffset(FVector(0.0f, -5.0f, 0.0f));
	}
	Super::Tick(DeltaTime);

}

// プログラムかBP経由でデータアセット設定 ※BP側で一度だけ読み込むように!
void ATMMAItemBase::SetSoftItemAsset(TSoftObjectPtr<UTMMAItemDataAsset> InSoftItemAsset)
{
	SoftItemDataAsset = InSoftItemAsset;
}

// データアセット再読み込みフラグ 
void ATMMAItemBase::SetReloadAssetFlag(bool InReloadAsset)
{
	ReloadAssetFlag = InReloadAsset;
}
