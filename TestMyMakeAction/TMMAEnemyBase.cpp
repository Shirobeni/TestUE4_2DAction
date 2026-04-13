// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAEnemyBase.h"
#include "Math/Rotator.h"

// Sets default values
ATMMAEnemyBase::ATMMAEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMMAEnemyBase::BeginPlay()
{
	InitStateByBeginPlay();
	StartEnemyPosition = this->GetActorLocation();
	LivingTime = 0;
	InitPatternStatus();
	// タイマー実行イベントの設定
	GetWorldTimerManager().SetTimer(TimerEventHandle, this, &ATMMAEnemyBase::OnEventByTimer, TimerEventFlame, true);
	Super::BeginPlay();
}

void ATMMAEnemyBase::InitStateByBeginPlay()
{
	SetEnemyStatusByAsset();
	if (ATestMyMakeActionGameModeBase* CastedGameMode = Cast<ATestMyMakeActionGameModeBase>(UGameplayStatics::GetGameMode(this))) {
		SetMainGameMode(CastedGameMode);
		if (ATMMAGameStateBase* CastedGameState = Cast<ATMMAGameStateBase>(UGameplayStatics::GetGameState(this))) {
			SetMainGameState(CastedGameState);
			SetShotClassArraySoftToSubclass();
			SetActorClassArraySoftToSubClass();
			SetRandomDefeatedFireSoftToSubclass();
		}
	}
}

void ATMMAEnemyBase::FunctionByTimerEvent()
{
	// とりあえず現状は空…かな
}

void ATMMAEnemyBase::ShotDelayFunction(float* InShotFloat, float InShotDelayFloat, TFunction<void()> ShotFuncCallBack)
{
	// ポインタ参照で、ショット時間用の変数の値を加算
	*InShotFloat += TimerEventFlame;
	if (*InShotFloat >= InShotDelayFloat) {
		// 処理実行.
		ShotFuncCallBack();
		*InShotFloat -= InShotDelayFloat;
	}
	// パターン切り替え時はリセットする.
	if ((PatternCountChangeMod >= 1) &&  (PatternCount % PatternCountChangeMod == 0)) {
		*InShotFloat = 0.0f;
	}
}


void ATMMAEnemyBase::Damage_Implementation(int InDamage, bool IsTimes)
{
	DamageOrDestroyEnemy(InDamage, IsTimes);
}

void ATMMAEnemyBase::DestroyFunction()
{
	SpawnDefeatedPerticleAndSe(DefeatParticleObj, DefeatSoundObj, this->GetActorLocation());
	Destroy();
}

void ATMMAEnemyBase::SetEnemyHp(int InHp)
{
	Hp = InHp;
}

void ATMMAEnemyBase::SetEnemyScore(int InScore)
{
	Score = InScore;
}

bool ATMMAEnemyBase::setEnemyStatus(FName SetRowName, FEnemyTableRow& EnemyParam)
{
	if (DataTable != nullptr) {
		FEnemyTableRow* EnemyRecord = DataTable->FindRow<FEnemyTableRow>(SetRowName, "");
		if (EnemyRecord != nullptr) {
			SetEnemyHp(EnemyRecord->Hp);
			SetEnemyScore(EnemyRecord->Score);
			return true;
		}
	}
	return false;
}

void ATMMAEnemyBase::SetEnemyStatusByAsset()
{
	EnemyDataAsset = SoftEnemyDataAsset.LoadSynchronous();
	if (EnemyDataAsset != nullptr) {
		Hp = EnemyDataAsset->Hp;
		Score = EnemyDataAsset->Score;
		// ボスとあるけど…共通化のためそれ以外の種類の敵も一応
		// TODO:: 関数名変えたい
		SetDamageAndDefeatedSoundAndParticleBySoft(
			EnemyDataAsset->SoftDamageSound,
			EnemyDataAsset->SoftDefeatedSound,
			EnemyDataAsset->SoftDeathrattleSound,
			EnemyDataAsset->SoftDefeatBossSmallSound,
			EnemyDataAsset->SoftDefeatBossSemiSound,
			EnemyDataAsset->SoftDamageParticle,
			EnemyDataAsset->SoftDefeateParticle,
			EnemyDataAsset->SoftDefeatBossSmallParticle
		);
		// 生成対象オブジェクト
		int SpawnActorSoftClasListNum = EnemyDataAsset->SpawnActorSoftClassList.Num();
		if (SpawnActorSoftClasListNum >= 1) {
			for (int idx = 0; idx < SpawnActorSoftClasListNum; idx++) {
				TSoftClassPtr<AActor> SpawnActorSoftClass = EnemyDataAsset->SpawnActorSoftClassList[idx];
				SpawnActorSoftList.Insert(SpawnActorSoftClass, idx);
			}
		}
		int ShotSoftClassNum = EnemyDataAsset->SoftShotEnemyBulletClassList.Num();
		if (ShotSoftClassNum >= 1) {
			for (int idx = 0; idx < ShotSoftClassNum; idx++) {
				TSoftClassPtr<ATMMAEnemyBulletBase> ShotSoftClass = EnemyDataAsset->SoftShotEnemyBulletClassList[idx];
				SoftShotEnemyBulletList.Insert(ShotSoftClass, idx);
			}
		}
		ParentSkeltalMesh = EnemyDataAsset->SoftSkeltalMesh.LoadSynchronous();
		for (int i = 0; i < EnemyDataAsset->SoftSkeltalMaterialList.Num(); i++) {
			UMaterial* SkeltalMaterial = EnemyDataAsset->SoftSkeltalMaterialList[i].LoadSynchronous();
			if (SkeltalMaterial != nullptr) {
				SkeltalMaterialArray.Add(SkeltalMaterial);
			}
		}
		for (int i = 0; i < EnemyDataAsset->SoftStaticMeshList.Num(); i++) {
			UStaticMesh* ChildStaticMesh = EnemyDataAsset->SoftStaticMeshList[i].LoadSynchronous();
			if (ChildStaticMesh != nullptr) {
				ChildStaticMeshList.Insert(ChildStaticMesh, i);
			}
		}
		int SoftSkeletalMeshListNum = EnemyDataAsset->SoftChildSkeletalMeshList.Num();
		if (SoftSkeletalMeshListNum >= 1) {
			for (int i = 0; i < SoftSkeletalMeshListNum; i++) {
				USkeletalMesh* ChileSkeletalMesh = EnemyDataAsset->SoftChildSkeletalMeshList[i].LoadSynchronous();
				if (ChileSkeletalMesh != nullptr) {
					ChildSkeltalMeshList.Insert(ChileSkeletalMesh, i);
				}
			}
		}
	}
}

void ATMMAEnemyBase::DamageOrDestroyEnemy(int InDamageParam, bool IsTimes)
{
//	if ((IsValid(this)) && (this->WasRecentlyRendered(0.0))) {
	if ((IsValid(this) == false) || (this->WasRecentlyRendered(0.0) == false)) {
		// 何もしない.
		return;
	}
	if ((this->ActorHasTag("Boss") == true && (GameMode != nullptr && GameMode->GetIsBossBattle() == true)) || (this->ActorHasTag("Boss") == false)) {
		if (IsDefeated == true) {
			// もう倒されているなら何もしない
			return;
		}
		EnemyDamage(InDamageParam);
		if ((DamageParticle != nullptr) && (DamageSound != nullptr)) {
			UParticleSystem* SpawnDamageParticle = DamageParticle.LoadSynchronous();
			UTMMAActorLibrary::SpawnSeAndParticle(this, SpawnDamageParticle, DamageSound, this->GetActorLocation(), FVector(1.0, 1.0, 1.0));
		}
		if (Hp <= 0) {
			if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(MainGameState) == true) {
				if (MainGameState->GetClass()->ImplementsInterface(UGameStateInterface::StaticClass())) {
					if (IsTimes == true) {
						Score = Score * 2.0f;
					}
					if (this->ActorHasTag("Boss") == true) {
						IGameStateInterface::Execute_AddEnemyScore(MainGameState, Score);
					}
					else {
						IGameStateInterface::Execute_AddEnemyScoreByDiff(MainGameState, Score);
					}
				}
				FTransform SelfTransform = this->GetActorTransform();
				SelfTransform.SetLocation(this->GetActorLocation());
				SpawnRandomDefeatedFire(SelfTransform);
				FVector EnemyLocation = this->GetActorLocation();
				EnemyLocation.X += 150.0f;
				SpawnDestroyExplotion(EnemyLocation);
			}
			// ボスキャラだった場合の処理
			if (this->ActorHasTag("Boss") == true) {
				MainGameState->AddStageTime(60.0f);
				DestroyAllSpawnActor();
				float DestroyTime = 1.0f;
				if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(GameMode) == true) {
					if (this->ActorHasTag("StageBoss") == true) {
						DestroyTime = 3.0f;
						GameMode->SetIsStageBossBattle(false);
						GameMode->SetIsClear(true);
						GameMode->TakeStageClear();
					}
					else {
						if ((GameMode->GetCurrentStage() != ECurrentStage::Stage5) || (MainGameState->GetCurrentStage() != ECurrentStageEnum::Stage5)) {
							GameMode->SetIsBossBattle(false);
							GameMode->ViewNavigation();
						}
					}
				}
				SetIsDefeated(true);
				FTimerHandle _TimerHandle;
				GetWorldTimerManager().SetTimer(_TimerHandle, this, &ATMMAEnemyBase::DestroyFunction, DestroyTime, false);
			}
			else {
				Destroy();
			}
		}
	}
}

void ATMMAEnemyBase::SpawnDestroyExplotion_Implementation(FVector InVector)
{
	if (this->ActorHasTag("Boss") == true) {
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(DeathrattleSoundObj) == true) {
			UGameplayStatics::PlaySound2D(this->GetWorld(), DeathrattleSoundObj, 1.0f, 1.0f, 0.0f, nullptr, this);
		}
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(RandomDefeatedFire) == true) {
			FVector RandomAroundAxis = UKismetMathLibrary::RotateAngleAxis(InVector, UKismetMathLibrary::RandomFloatInRange(0.0, 60.0), FVector(0.0, 0.0, 1.0));
			FTransform SpawnTransform = this->GetActorTransform();
			SpawnTransform.SetLocation(RandomAroundAxis);
			for (int i = 0; i < 6; i++) {
				GetWorld()->SpawnActor<AActor>(RandomDefeatedFire, SpawnTransform);
			}
		}
		FTimerHandle _TimerHandle;
		GetWorldTimerManager().SetTimer(_TimerHandle, this, &ATMMAEnemyBase::SpawnBossExplosionSmall, 0.05f, true);
	}
	else {
		SpawnRandomDefeatedParticleAndSe(DefeatParticleObj, DefeatSoundObj, InVector);
	}

}

void ATMMAEnemyBase::SpawnBossExplosionSmall()
{
	//　基本は小爆発の音とパーティクルがあるか判定
	if ((UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(DefeatBossSmallParticleObj) == true) && (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(DefeatBossSmallSoundObj) == true)) {
		USoundBase* SpawnDefeatSoundObj = DefeatBossSmallSoundObj;
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(DefeatBossSemiSoundObj) == true) {
			// 中爆発音が設定しているのであれば、ランダムでたまに鳴らすようにする.
			int RandomInt = FMath::RandRange(1, 12);
			switch (RandomInt)
			{
			case 12:
				SpawnDefeatSoundObj = DefeatBossSemiSoundObj;
				break;
			default:
				SpawnDefeatSoundObj = DefeatBossSmallSoundObj;
				break;
			}
		}
		SpawnRandomDefeatedParticleAndSe(DefeatBossSmallParticleObj, SpawnDefeatSoundObj, this->GetActorLocation());
	}
}

void ATMMAEnemyBase::MoveEnemy(FVector AddVector)
{
	FVector EnemyLocation = this->GetActorLocation();
	SetActorLocation(FVector(EnemyLocation.X + AddVector.X, EnemyLocation.Y + AddVector.Y, EnemyLocation.Z + AddVector.Z));
}

void ATMMAEnemyBase::SetMaxLivingTime(float InMaxLivingTime)
{
	MaxLivingTime = InMaxLivingTime;
}

void ATMMAEnemyBase::AddLivingTime(float AddTimeParam)
{
	// 0の場合は恐らく時間で死なないようにしておく
	if(MaxLivingTime > 0)
	{
		LivingTime += AddTimeParam;
		if (LivingTime > MaxLivingTime) {
			this->Destroy();
		}
	}
}

void ATMMAEnemyBase::InitPatternStatus()
{
	PatternCount = 0;
	PatternType = 0;
	SetPatternTransForm(1);
}


// Called every frame
void ATMMAEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATMMAEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATMMAEnemyBase::SetPatternCount(int InPatternCount)
{
	PatternCount = InPatternCount;
}

void ATMMAEnemyBase::CountingPatternCount(int ChangeMod, int EndCount)
{
	PatternCount++;
	if (PatternCount % ChangeMod == 0) {
		PatternType++;
	} 
	if (PatternCount > EndCount) {
		PatternType = 0;
		PatternCount = 0;
	}
}

void ATMMAEnemyBase::SetPatternType(int InPatterrnType)
{
	PatternType = InPatterrnType;
}

void ATMMAEnemyBase::LoopPatternType(int LimitType) {
	PatternType++;
	if (PatternType == LimitType) {
		PatternType = 0;
	}
}

// 形態変化
void ATMMAEnemyBase::SetPatternTransForm(int InPatternTransform)
{
	PatternTransform = InPatternTransform;
}

void ATMMAEnemyBase::SetTransformWaitFlag(bool InTransformWaitFlag)
{
	TransformWaitFlag = InTransformWaitFlag;
}

// タイマー設定
//template<typename T>
//void ATMMAEnemyBase::SetTimerFromFunction(FTimerHandle InHandle, T* TargetObj, void(T::* Func)(), float Rate)
//{
//
//}

bool ATMMAEnemyBase::GetShotLag(int OnFlagParam)
{
	int ShotLagCount = PatternCount % (PatternType + 1);
	if ((ShotLagCount % OnFlagParam) == 0) {
		return true;
	}
	else {
		return false;
	}

}

void ATMMAEnemyBase::SetShotClassArraySoftToSubclass()
{
	int SoftShotEnemyBulletListNum = SoftShotEnemyBulletList.Num();
	if (SoftShotEnemyBulletListNum >= 1) {
		for (int idx = 0; idx < SoftShotEnemyBulletListNum; idx++) {
			if (SoftShotEnemyBulletList[idx] != nullptr) {
				ShotEnemyBulletList.Add(SoftShotEnemyBulletList[idx].LoadSynchronous());
			}
		}
	}
}

void ATMMAEnemyBase::SetActorClassArraySoftToSubClass()
{
	int SoftActorClassListNum = SpawnActorSoftList.Num();
	if (SoftActorClassListNum >= 1) {
		for (int idx = 0; idx < SoftActorClassListNum; idx++) {
			if (SpawnActorSoftList[idx] != nullptr) {
				SpawnActorClassList.Add(SpawnActorSoftList[idx].LoadSynchronous());
			}
		}
	}
}



void ATMMAEnemyBase::ShotEnemyBulletAim(FVector StartVector, FVector TargetVector,TSubclassOf<AActor> BulletActor, FVector InScale, AActor*& SpawnShot)
{
	ACharacter* aPlayerCharacter = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
		this->GetActorLocation(),
		TargetVector
	);
	FVector RoVector = LookAtRotation.RotateVector(StartVector);
	// 引数の各値で0以下ののものはデフォルトの1に設定。
	if (InScale.X <= 0) {
		InScale.X = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	FTransform ShotTransform = UKismetMathLibrary::MakeTransform(this->GetActorLocation() + RoVector, LookAtRotation, InScale);
	if (BulletActor != nullptr) {
		AActor* ShotActor = GetWorld()->SpawnActor<AActor>(BulletActor, ShotTransform);
//		if (IsValid(ShotActor)) {
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(ShotActor) == true){
			ShotActor->SetActorTransform(ShotTransform);
			SpawnShot = ShotActor;
		}
		else {
			SpawnShot = nullptr;
		}
	} else{
		SpawnShot = nullptr;
	}
}

void ATMMAEnemyBase::ShotEnemyBulletAimBySoft(FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, AActor*& SpawnShot)
{
//	if (SoftBulletActor != nullptr) {
		TSubclassOf<ATMMAEnemyBulletBase> BulletActor = SoftBulletActor.LoadSynchronous();
		ShotEnemyBulletAim(StartVector, TargetVector, BulletActor, InScale, SpawnShot);
//	}
}

void ATMMAEnemyBase::ShotEnemyBulletAimByIndex(FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, AActor*& SpawnShot)
{
	SpawnShot = nullptr;
	if ((ShotEnemyBulletList.Num() >= 1 ) && (ShotEnemyBulletList[BulletIndex] != nullptr)) {
		ShotEnemyBulletAim(StartVector, TargetVector, ShotEnemyBulletList[BulletIndex], InScale, SpawnShot);
	}
}


void ATMMAEnemyBase::ShotEnemyBulletAimForVerctor(FVector SetVector, FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, AActor*& SpawnShot)
{
	if (InScale.X <= 0) {
		InScale.X = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	FTransform ShotTransform;
	UTMMAActorLibrary::GetAimTransformForVector(SetVector, StartVector, TargetVector, InScale, ShotTransform);
	if (BulletActor != nullptr) {
		AActor* ShotActor = GetWorld()->SpawnActor<AActor>(BulletActor, ShotTransform);
//		if (IsValid(ShotActor)) {
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(ShotActor) == true) {
			ShotActor->SetActorTransform(ShotTransform);
			SpawnShot = ShotActor;
		}
		else {
			SpawnShot = nullptr;
		}
	}
	else {
		SpawnShot = nullptr;
	}

}

void ATMMAEnemyBase::ShotEnemyBulletAimForVertorBySoft(FVector SetVector, FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, AActor*& SpawnShot)
{
//	if (SoftBulletActor != nullptr) {
		TSubclassOf<ATMMAEnemyBulletBase> BulletActor = SoftBulletActor.LoadSynchronous();
		ShotEnemyBulletAimForVerctor(SetVector, StartVector, TargetVector, BulletActor, InScale, SpawnShot);
//	}
}

void ATMMAEnemyBase::ShotEnemyBulletAimForVerctorByIndex(FVector SetVector, FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, AActor*& SpawnShot)
{
	SpawnShot = nullptr;
	if ((ShotEnemyBulletList.Num() >= 1) && (ShotEnemyBulletList[BulletIndex] != nullptr)) {
		ShotEnemyBulletAimForVerctor(SetVector, StartVector, TargetVector, ShotEnemyBulletList[BulletIndex], InScale, SpawnShot);
	}
}



void ATMMAEnemyBase::GetEnemyBulletAim(FVector SetVector, FVector TargetVector, FVector InScale, FTransform& GetTransform)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
		this->GetActorLocation(),
		TargetVector
	);
	FVector RoVector = LookAtRotation.RotateVector(SetVector);
	GetTransform = UKismetMathLibrary::MakeTransform(this->GetActorLocation() + RoVector, LookAtRotation, InScale);
}

void ATMMAEnemyBase::ShotEnemyWayBulletAim(FVector SetVector, FVector TargetVector, FVector InScale, int CombineIndex, float CombineAngle, TSubclassOf<AActor> BulletActor)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
		this->GetActorLocation(),
		TargetVector
	);
	FVector RoVector = LookAtRotation.RotateVector(SetVector);
	if (BulletActor != nullptr) {
		for (int i = 0; i < CombineIndex; i++) {
			LookAtRotation += FRotator(i * CombineAngle, 0, 0);
			FTransform ShotTransform = UKismetMathLibrary::MakeTransform(this->GetActorLocation() + RoVector, LookAtRotation, InScale);
			AActor* ShotActor = GetWorld()->SpawnActor<AActor>(BulletActor, ShotTransform);
//			if (IsValid(ShotActor)) {
			if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(ShotActor) == true) {
				ShotActor->SetActorTransform(ShotTransform);
			}
		}
	}
}

void ATMMAEnemyBase::ShotEnemyWayBulletAimByIndex(FVector SetVector, FVector TargetVector, FVector InScale, int CombineIndex, float CombineAngle, int BulletIndex)
{
	if ((ShotEnemyBulletList.Num() >= 1) && (ShotEnemyBulletList[BulletIndex] != nullptr)) {
		ShotEnemyWayBulletAim(SetVector, TargetVector, InScale, CombineIndex, CombineAngle, ShotEnemyBulletList[BulletIndex]);
	}
}

void ATMMAEnemyBase::ShotEnemyBulletXVector(FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, AActor*& SpawnShot)
{
	FRotator LookAtRotation = TargetVector.Rotation();
	LookAtRotation.Roll = 0.0;
	FVector RoVector = LookAtRotation.RotateVector(StartVector);
	// 引数の各値で0以下ののものはデフォルトの1に設定。
	if (InScale.X <= 0) {
		InScale.X = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	FTransform ShotTransform = UKismetMathLibrary::MakeTransform(this->GetActorLocation() + RoVector, LookAtRotation, InScale);
	if (BulletActor != nullptr) {
		AActor* ShotActor = GetWorld()->SpawnActor<AActor>(BulletActor, ShotTransform);
//		if (IsValid(ShotActor)) {
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(ShotActor) == true) {
			ShotActor->SetActorTransform(ShotTransform);
			SpawnShot = ShotActor;
		}
		else {
			SpawnShot = nullptr;
		}
	}
	else {
		SpawnShot = nullptr;
	}
}

void ATMMAEnemyBase::ShotEnemyBulletXVectorBySoft(FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, AActor*& SpawnShot)
{
	TSubclassOf<ATMMAEnemyBulletBase> BulletActor = SoftBulletActor.LoadSynchronous();
	if (!BulletActor) return;
	ShotEnemyBulletXVector(StartVector, TargetVector, BulletActor, InScale, SpawnShot);
}

void ATMMAEnemyBase::ShotEnemyBulletXVectorByIndex(FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, AActor*& SpawnShot)
{
	SpawnShot = nullptr;
	if ((ShotEnemyBulletList.Num() >= 1) && (ShotEnemyBulletList[BulletIndex])) {
		ShotEnemyBulletXVector(StartVector, TargetVector, ShotEnemyBulletList[BulletIndex], InScale, SpawnShot);
	}
}

void ATMMAEnemyBase::ShotEnemyBulletXVectorForVector(FVector SetVector, FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, AActor*& SpawnShot)
{
	if (InScale.X <= 0) {
		InScale.X = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	FTransform ShotTransform;
	UTMMAActorLibrary::GetXVectorTransform(SetVector, StartVector, TargetVector, InScale, ShotTransform);
	if (BulletActor != nullptr) {
		AActor* ShotActor = GetWorld()->SpawnActor<AActor>(BulletActor, ShotTransform);
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(ShotActor) == true) {
			ShotActor->SetActorTransform(ShotTransform);
			SpawnShot = ShotActor;
		}
		else {
			SpawnShot = nullptr;
		}
	}
	else {
		SpawnShot = nullptr;
	}
}

void ATMMAEnemyBase::ShotEnemyBulletXVectorForVectorBySoft(FVector SetVector, FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, AActor*& SpawnShot)
{
	TSubclassOf<ATMMAEnemyBulletBase> BulletActor = SoftBulletActor.LoadSynchronous();
	if (!BulletActor) return;
	ShotEnemyBulletAimForVerctor(SetVector, StartVector, TargetVector, BulletActor, InScale, SpawnShot);
}

void ATMMAEnemyBase::ShotEnemyBulletXVectorForVectorByIndex(FVector SetVector, FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, AActor*& SpawnShot)
{
	SpawnShot = nullptr;
	if ((ShotEnemyBulletList.Num() >= 1) && (ShotEnemyBulletList[BulletIndex] != nullptr)) {
		ShotEnemyBulletXVectorForVector(SetVector, StartVector, TargetVector, ShotEnemyBulletList[BulletIndex], InScale, SpawnShot);
	}
}


void ATMMAEnemyBase::ShotEnemyBulletXVectorByCombine(FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, FRotator AddRotate, AActor*& SpawnShot)
{
	FRotator LookAtRotation = TargetVector.Rotation();
	LookAtRotation.Roll = 0.0;
	FVector RoVector = LookAtRotation.RotateVector(StartVector);
	FRotator CombinedRotator = LookAtRotation + AddRotate;
	// 引数の各値で0以下ののものはデフォルトの1に設定。
	if (InScale.X <= 0) {
		InScale.X = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	FTransform ShotTransform = UKismetMathLibrary::MakeTransform(this->GetActorLocation() + RoVector, CombinedRotator, InScale);
	if (BulletActor != nullptr) {
		AActor* ShotActor = GetWorld()->SpawnActor<AActor>(BulletActor, ShotTransform);
		if (IsValid(ShotActor)) {
			ShotActor->SetActorTransform(ShotTransform);
			SpawnShot = ShotActor;
		}
		else {
			SpawnShot = nullptr;
		}
	}
	else {
		SpawnShot = nullptr;
	}
}

void ATMMAEnemyBase::ShotEnemyBulletXVectorByCombineBySoft(FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, FRotator AddRotate, AActor*& SpawnShot)
{
	TSubclassOf<ATMMAEnemyBulletBase> BulletActor = SoftBulletActor.LoadSynchronous();
	if (!BulletActor) return;
	ShotEnemyBulletXVectorByCombine(StartVector, TargetVector, BulletActor, InScale, AddRotate, SpawnShot);
}

void ATMMAEnemyBase::ShotEnemyBulletXVectorByCombineByIndex(FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, FRotator AddRotate, AActor*& SpawnShot)
{
	SpawnShot = nullptr;
	if ((ShotEnemyBulletList.Num() >= 1) && (ShotEnemyBulletList[BulletIndex])) {
		ShotEnemyBulletXVectorByCombine(StartVector, TargetVector, ShotEnemyBulletList[BulletIndex], InScale, AddRotate, SpawnShot);
	}

}


void ATMMAEnemyBase::ShotEnemyBulletXVectorForVectorByCombine(FVector SetVector, FVector StartVector, FVector TargetVector, TSubclassOf<AActor> BulletActor, FVector InScale, FRotator AddRotate, AActor*& SpawnShot)
{
	if (InScale.X <= 0) {
		InScale.X = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	if (InScale.Y <= 0) {
		InScale.Y = 1.0;
	}
	FTransform ShotTransform;
	UTMMAActorLibrary::GetXVectorTransformByCombine(SetVector, StartVector, TargetVector, InScale, AddRotate, ShotTransform);
	if (BulletActor != nullptr) {
		AActor* ShotActor = GetWorld()->SpawnActor<AActor>(BulletActor, ShotTransform);
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(ShotActor) == true) {
			ShotActor->SetActorTransform(ShotTransform);
			SpawnShot = ShotActor;
		}
		else {
			SpawnShot = nullptr;
		}
	}
	else {
		SpawnShot = nullptr;
	}
}

void ATMMAEnemyBase::ShotEnemyBulletXVectorForVectorByCombineBySoft(FVector SetVector, FVector StartVector, FVector TargetVector, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor, FVector InScale, FRotator AddRotate, AActor*& SpawnShot)
{
	TSubclassOf<ATMMAEnemyBulletBase> BulletActor = SoftBulletActor.LoadSynchronous();
	if (!BulletActor) return;
	ShotEnemyBulletXVectorForVectorByCombine(SetVector, StartVector, TargetVector, BulletActor, InScale, AddRotate, SpawnShot);
}

void ATMMAEnemyBase::ShotEnemyBulletXVectorForVectorByCombineByIndex(FVector SetVector, FVector StartVector, FVector TargetVector, int BulletIndex, FVector InScale, FRotator AddRotate, AActor*& SpawnShot)
{
	SpawnShot = nullptr;
	if ((ShotEnemyBulletList.Num() >= 1) && (ShotEnemyBulletList[BulletIndex] != nullptr)) {
		ShotEnemyBulletXVectorForVectorByCombine(SetVector, StartVector, TargetVector, ShotEnemyBulletList[BulletIndex], InScale, AddRotate, SpawnShot);
	}

}

void ATMMAEnemyBase::ShotEnemyWayBulletAimBySoft(FVector SetVector, FVector TargetVector, FVector InScale, int CombineIndex, float CombineAngle, TSoftClassPtr<ATMMAEnemyBulletBase> SoftBulletActor)
{
	TSubclassOf<ATMMAEnemyBulletBase> BulletActor = SoftBulletActor.LoadSynchronous();
	if (!BulletActor) return;
	ShotEnemyWayBulletAim(SetVector, TargetVector, InScale, CombineIndex, CombineAngle, BulletActor);
}



void ATMMAEnemyBase::EnemyDamage(int InDamage)
{
	Hp -= InDamage;
	if (DamageSound != nullptr) {
		UGameplayStatics::PlaySound2D(GetWorld(), DamageSound, 1.0f, 1.0f, 0.0f, nullptr, this);
	}
}

void ATMMAEnemyBase::SetDamageAndDefeatedSoundAndParticleBySoft(TSoftObjectPtr<USoundBase> InSoftDamageSound, TSoftObjectPtr<class USoundBase> InSoftDefeatSound, TSoftObjectPtr<class USoundBase> InSoftDeathrattleSound, TSoftObjectPtr<class USoundBase> InSoftDefeatBossSmallSound, TSoftObjectPtr<class USoundBase> InSoftDefeatBossSemiSound, TSoftObjectPtr<class UParticleSystem> InDamageParticle, TSoftObjectPtr<class UParticleSystem> InDefeatParticle, TSoftObjectPtr<class UParticleSystem> InDefeatBossSmallParticle)
{
	DamageSound = InSoftDamageSound.LoadSynchronous();
	DefeatSoundObj = InSoftDefeatSound.LoadSynchronous();
	DeathrattleSoundObj = InSoftDeathrattleSound.LoadSynchronous();
	DefeatBossSmallSoundObj = InSoftDefeatBossSmallSound.LoadSynchronous();
	DefeatBossSemiSoundObj = InSoftDefeatBossSemiSound.LoadSynchronous();
	DamageParticleObj = InDamageParticle.LoadSynchronous();
	DefeatParticleObj = InDefeatParticle.LoadSynchronous();
	DefeatBossSmallParticleObj = InDefeatBossSmallParticle.LoadSynchronous();
}

void ATMMAEnemyBase::SetDamageSound(USoundBase* InSound)
{
	DamageSound = InSound;
}

void ATMMAEnemyBase::SetDamageSoundBySoft(TSoftObjectPtr<USoundBase> InSoftDamageSound)
{
	USoundBase* DamageSoundObj = InSoftDamageSound.LoadSynchronous();
	DamageSound = DamageSoundObj;
}

void ATMMAEnemyBase::SetDefeatForEnemy(TSoftObjectPtr<class USoundBase> InSoftDefeatSound, TSoftObjectPtr<class UParticleSystem> InDamageParticle, TSoftObjectPtr<class UParticleSystem> InDefeateParticle)
{
	SoftDefeatSound = InSoftDefeatSound;
	DamageParticle = InDamageParticle;
	DefeatParticle = InDefeateParticle;
	SetSoftToObjSeAndParticle();
}

void ATMMAEnemyBase::SetDefeatForBoss(TSoftObjectPtr<class USoundBase> InSoftDefeatSound, TSoftObjectPtr<class USoundBase> InSoftDeathrattleSound, TSoftObjectPtr<class USoundBase> InSoftDefeatBossSmallSound, TSoftObjectPtr<class USoundBase> InSoftDefeatBossSemiSound, TSoftObjectPtr<class UParticleSystem> InDamageParticle, TSoftObjectPtr<class UParticleSystem> InDefeateParticle, TSoftObjectPtr<class UParticleSystem> InDefeatBossSmallParticle)
{
	SoftDefeatSound = InSoftDefeatSound;
	SoftDeathrattleSound = InSoftDeathrattleSound;
	SoftDefeatBossSmallSound = InSoftDefeatBossSmallSound;
	SoftDefeatBossSemiSound = InSoftDefeatBossSemiSound;
	DamageParticle = InDamageParticle;
	DefeatParticle = InDefeateParticle;
	DefeatBossSmallParticle = InDefeatBossSmallParticle;
	SetSoftToObjSeAndParticle();
}

void ATMMAEnemyBase::SetSoftToObjSeAndParticle() 
{
	DefeatSoundObj = SoftDefeatSound.LoadSynchronous();
	DeathrattleSoundObj = SoftDeathrattleSound.LoadSynchronous();
	DefeatBossSmallSoundObj = SoftDefeatBossSmallSound.LoadSynchronous();
	DefeatBossSemiSoundObj = SoftDefeatBossSemiSound.LoadSynchronous();
	DamageParticleObj = DamageParticle.LoadSynchronous();
	DefeatParticleObj = DefeatParticle.LoadSynchronous();
	DefeatBossSmallParticleObj = DefeatBossSmallParticle.LoadSynchronous();
}

void ATMMAEnemyBase::SetRandomDefeatedFireSoftToSubclass()
{
	if (SoftRandomDefeatedFire != nullptr) {
		RandomDefeatedFire = SoftRandomDefeatedFire.LoadSynchronous();
	}
}

void ATMMAEnemyBase::SpawnRandomDefeatedFire(FTransform InTransform)
{
	int RandomInt = FMath::RandRange(0, 5);
	if (RandomInt == 3) {
		if (RandomDefeatedFire != nullptr) {
			GetWorld()->SpawnActor<AActor>(RandomDefeatedFire, InTransform);
		}
	}
}

void ATMMAEnemyBase::SetAndSyncroGameMode(TSoftObjectPtr<class ATestMyMakeActionGameModeBase> InGameModeObject)
{
	GameModeObject = InGameModeObject;
	GameMode = GameModeObject.LoadSynchronous();
}

void ATMMAEnemyBase::SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode)
{
	GameMode = InMainGameMode;
}

void ATMMAEnemyBase::SetMainGameState(ATMMAGameStateBase* InMainGameState)
{
	MainGameState = InMainGameState;
}

void ATMMAEnemyBase::SpawnDefeatedPerticleAndSe(UParticleSystem* InParticle, USoundBase* InSe, FVector InVector)
{
	UGameplayStatics::PlaySound2D(GetWorld(), InSe, 1.0f, 1.0f, 0.0f, nullptr, this);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), InParticle, InVector, FRotator(0.0f, 0.0f, 0.0f), true, EPSCPoolMethod::None, true);
}

void ATMMAEnemyBase::SpawnRandomDefeatedParticleAndSe(UParticleSystem* InParticle, USoundBase* InSe, FVector InVector)
{
	int RandomInt = FMath::RandRange(0,6);
	FVector ParticleVector = FVector(0.0, 0.0, 0.0);
	switch (RandomInt) {
		default:
			ATMMAEnemyBase::SpawnDefeatedPerticleAndSe(InParticle, InSe, InVector);
			break;
		case 2:
		case 4:
			for (int i = 0; i < 7; i++) {
				ATMMAEnemyBase::SpawnDefeatedPerticleAndSe(InParticle, InSe, (InVector + ParticleVector));
				ParticleVector += FVector(10.0f, 100.0f, 30.0f);
			}
			break;
		case 3:
			for (int i = 0; i < 7; i++) {
				float RandomFloat = FMath::FRandRange(-4, 4);
				ATMMAEnemyBase::SpawnDefeatedPerticleAndSe(InParticle, InSe,  (InVector * RandomFloat));
			}
			break;
	}
}

void ATMMAEnemyBase::SetAddTime(float InAddTime) {
	AddTime = InAddTime;
}

bool ATMMAEnemyBase::LineTraceByTargetToPlayer(FVector StartVector, FVector TargetVector, float TraceDistance, ECollisionChannel TraceChannel, FHitResult& HitResult) {
	FVector TargetTrace = TargetVector * TraceDistance;
	TargetTrace += StartVector;
	FHitResult ResultOutHit;
	bool traceFlag = GetWorld()->LineTraceSingleByChannel(ResultOutHit, StartVector, TargetTrace, TraceChannel);
	HitResult = ResultOutHit;
	DrawDebugLine(GetWorld(), StartVector, TargetTrace, FColor::Red, false, 5.0);

	return traceFlag;
}

const FVector ATMMAEnemyBase::GetAimToPlayer(FVector EnemyVector, FVector PlayerVector)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(
		EnemyVector,
		PlayerVector
	);
	return LookAtRotation.RotateVector(EnemyVector);

}

const FVector ATMMAEnemyBase::GetDistanceAtPlayer()
{
	FVector EnemyVector = this->GetActorLocation();
	FVector PlayerVector = FVector(0.0, 0.0, 0.0);
	UTMMAActorLibrary::GetPlayerLocation(PlayerVector);
//	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
//	if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(PlayerActor) == true) {
//		PlayerVector = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0)->GetActorLocation();
//	}
	return EnemyVector - PlayerVector;
}

const bool ATMMAEnemyBase::GetInDistanceAtPlayerX(float PlusDistance, float MinusDistance)
{
	bool ReturnBool = false;
	// クラッシュ防止のチェック
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(PlayerActor) == true) {
		ReturnBool = UTMMAActorLibrary::GetIsInDistanceX(this, PlayerActor, PlusDistance, MinusDistance);
	}
	return ReturnBool;
}

const bool ATMMAEnemyBase::GetInDistanceAtPlayerY(float PlusDistance, float MinusDistance)
{
	bool ReturnBool = false;
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(PlayerActor) == true) {
		ReturnBool = UTMMAActorLibrary::GetIsInDistanceY(this, PlayerActor, PlusDistance, MinusDistance);
	}
	return ReturnBool;
}

const bool ATMMAEnemyBase::GetInDistanceAtPlayerZ(float PlusDistance, float MinusDistance)
{
	bool ReturnBool = false;
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(PlayerActor) == true) {
		ReturnBool = UTMMAActorLibrary::GetIsInDistanceZ(this, PlayerActor, PlusDistance, MinusDistance);
	}
	return ReturnBool;
}

TSubclassOf<ATMMAEnemyBulletBase> ATMMAEnemyBase::GetEnemyBulletBySubclass(int Index)
{
	if (ShotEnemyBulletList[Index] != nullptr) {
		return ShotEnemyBulletList[Index];
	}
	return nullptr;
}

void ATMMAEnemyBase::SetIsDefeated(bool InIsDefeated)
{
	IsDefeated = InIsDefeated;
}

// TODO::廃止予定
void ATMMAEnemyBase::AddSpawnActorList(AActor* SpawnActor)
{
	SpawnActorList.Add(SpawnActor);
}

void ATMMAEnemyBase::DestroyAllSpawnActor()
{
	TSubclassOf<ATMMAEnemyBulletBase> EnemuBulletClass;
	EnemuBulletClass = ATMMAEnemyBulletBase::StaticClass();
	TArray<AActor*> EnemuBullets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemuBulletClass, EnemuBullets);
	if (EnemuBullets.Num()) {
		for (int idx = 0; idx < EnemuBullets.Num(); idx++) {
			if (ATMMAEnemyBulletBase* EnemyBulletBase = Cast<ATMMAEnemyBulletBase>(EnemuBullets[idx])) {
				EnemuBullets[idx]->Destroy();
			}

		}
	}
	SpawnActorList.Empty();

}