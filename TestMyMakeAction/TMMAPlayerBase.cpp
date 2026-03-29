// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAPlayerBase.h"
#include "TMMAGameInstanceBase.h"
#include "GameState/TMMAGameStateBase.h"
#include "TestMyMakeAction/BulletBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATMMAPlayerBase::ATMMAPlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATMMAPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	SetShotClassBySoft();
	SetSoundAndParticleAll();
	TSubclassOf<ATMMAPlayerCameraBase> PlayerCameraClass = SoftPlayerCameraClass.LoadSynchronous();
	AActor* FindActor = UGameplayStatics::GetActorOfClass(GetWorld(), PlayerCameraClass);
	if (FindActor != nullptr) {
		UE_LOG(LogTemp, Log, TEXT("PlayerCameraFindOK."));
		if (ATMMAPlayerCameraBase* CastedPlayerCamera = Cast<ATMMAPlayerCameraBase>(FindActor)) {
			PlayerCamera = CastedPlayerCamera;
			UE_LOG(LogTemp, Log, TEXT("PlayerCameraCastOK."));
		}
	}
	if (UTMMAGameInstanceBase* MainGameInstance = Cast<UTMMAGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()))) {
		TakeOverPlayerStatusByInstance(MainGameInstance);
	}
	if (ATestMyMakeActionGameModeBase* CastedMainGameMode = Cast<ATestMyMakeActionGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))) {
		MainGameMode = CastedMainGameMode;
		SetMissileMode();
		SetInvinsible();
	}
}

// Called every frame
void ATMMAPlayerBase::Tick(float DeltaTime)
{
	if (IsAbleControll == true) {
		CheckAbleSword(200, -200, 100, -100);
		AddSwordWaitTime();
	}
	Super::Tick(DeltaTime);

}

void ATMMAPlayerBase::TakeOverPlayerStatusByInstance(UTMMAGameInstanceBase* InGameInstance)
{
	SetPlayerLife(InGameInstance->GetP1Life());
	SetShotType(InGameInstance->GetP1ShotType());
	SetShotLevel(InGameInstance->GetP1PowerLevel());
	SetBurstCount(InGameInstance->GetP1LeftBurst());
	SetIsAbleBurst(true);
	SetIsAbleControll(true);
}

void ATMMAPlayerBase::SetShotClassBySoft()
{
	if (RapidShotSoftClass != nullptr) {
		RapidShotClass = RapidShotSoftClass.LoadSynchronous();
	}
	if (HomingShotSoftClass != nullptr) {
		HomingShotClass = HomingShotSoftClass.LoadSynchronous();
	}
	if (FireShotSoftClass != nullptr) {
		FireShotClass = FireShotSoftClass.LoadSynchronous();
	}
	if (GrenadeShotSoftClass != nullptr) {
		GrenadeShotClass = GrenadeShotSoftClass.LoadSynchronous();
	}
	if (LaserShotSoftClass != nullptr) {
		LaserShotClass = LaserShotSoftClass.LoadSynchronous();
	}
	if (PlayerMissileSoftClass != nullptr) {
		PlayerMissile = PlayerMissileSoftClass.LoadSynchronous();
	}
}


void ATMMAPlayerBase::SetIsAbleControll(bool InIsAbleControll) {
	IsAbleControll = InIsAbleControll;
}

void ATMMAPlayerBase::SetIsPussingShotButton(bool InIsPussingShotButton)
{
	IsPussingShotButton = InIsPussingShotButton;
}

// Called to bind functionality to input
void ATMMAPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATMMAPlayerBase::SetPlayerCamera(ATMMAPlayerCameraBase* Camera)
{
	PlayerCamera = Camera;
}

void ATMMAPlayerBase::MoveLeft(FVector RunSpeed, float Value)
{
	if (Value != 0) {
		FVector PlayerLocation = this->GetActorLocation();
		FVector CameraLocation = PlayerCamera->GetActorLocation();
		if (PlayerLocation.Y - CameraLocation.Y >= -470) {
			AddMovementInput(RunSpeed, Value);
		}
	}
}

void ATMMAPlayerBase::MoveRignt(FVector RunSpeed, float Value)
{
	if (Value != 0) {
		FVector PlayerLocation = this->GetActorLocation();
		FVector CameraLocation = PlayerCamera->GetActorLocation();
		if (PlayerLocation.Y - CameraLocation.Y <= 470) {
			AddMovementInput(RunSpeed, Value);
		}
	}
}

void ATMMAPlayerBase::MoveUp(FVector RunSpeed, float Value)
{
	if (Value != 0) {
		FVector PlayerLocation = this->GetActorLocation();
		FVector CameraLocation = PlayerCamera->GetActorLocation();
		if (PlayerLocation.Z - CameraLocation.Z <= 230) {
			AddMovementInput(RunSpeed, Value);
		}
	}
}

void ATMMAPlayerBase::MoveDown(FVector RunSpeed, float Value)
{
	if (Value != 0) {
		FVector PlayerLocation = this->GetActorLocation();
		FVector CameraLocation = PlayerCamera->GetActorLocation();
		if (PlayerLocation.Z - CameraLocation.Z >= -230) {
			AddMovementInput(RunSpeed, Value);
		}
	}
}

void ATMMAPlayerBase::MoveCharacter(FVector RunSpeed, float Value)
{
	if (Value != 0) {
		FVector PlayerLocation = this->GetActorLocation();
//		FVector CameraLocation = PlayerCamera->GetActorLocation();
//		float BorderLocation_Y = PlayerLocation.Y - CameraLocation.Y;
//		float BorderLocation_Z = PlayerLocation.Z - CameraLocation.Z;
		if (PlayerLocation.Y < -476){
			SetActorLocation(FVector(PlayerLocation.X, -470, PlayerLocation.Z), true);
		}
		if ((PlayerLocation.Y > 526))
		{
			SetActorLocation(FVector(PlayerLocation.X, 520, PlayerLocation.Z), true);
		}
		if (PlayerLocation.Z < -250)
		{
			SetActorLocation(FVector(PlayerLocation.X, PlayerLocation.Y, -250), true);
		}
		if (PlayerLocation.Z > 270)
		{
			SetActorLocation(FVector(PlayerLocation.X, PlayerLocation.Y, 270), true);
		}
		AddActorWorldOffset((RunSpeed * Value * 4), true);
	}

}

void ATMMAPlayerBase::Shot(float VectorY, float VectorZ)
{
	if (BulletCount >= 1) {
		FVector ShotBulletAim = FVector(0.0, 1.0, 0.0);
		if (PlayerMode == EPlayerMode::Action) {
			ShotBulletAim = FVector(0.0, VectorY, VectorZ);
			if (this->bIsCrouched == true && this->bProxyIsJumpForceApplied == false) {
				ShotBulletAim.Z = 0.0;
			}
		}
		switch (ShotType)
		{
			case EShotType::Rapid:
				ShotRapid(ShotBulletAim);
				break;
			case EShotType::Homing:
				ShotHoming(ShotBulletAim);
				break;
			case EShotType::Fire:
				ShotFire(ShotBulletAim);
				break;
			case EShotType::Grenade:
				ShotGrenade(ShotBulletAim);
				break;
			case EShotType::Laser:
				ShotLaser(ShotBulletAim);
				break;
			default:
				break;
		}
	}
}

void ATMMAPlayerBase::ShotRapid(FVector InDirection)
{
	int WideFirstIndex = 0;
	int WideLastIndex = 0;
	if (RapidShotClass != nullptr) {
		switch (PlayerMode)
		{
		case EPlayerMode::Shooting :
				switch (ShotLevel)
				{
					case 2:
						WideFirstIndex = 0;
						WideLastIndex = 1;
						break;
					case 3:
						WideFirstIndex = -1;
						WideLastIndex = 1;
						break;
					default:
						break;
				}
				break;
			default:
				switch (ShotLevel)
				{
					case 2:
						WideFirstIndex = 0;
						WideLastIndex = 1;
						break;
					case 3:
						WideFirstIndex = 0;
						WideLastIndex = 2;
						break;
					default:
						break;
				}
				break;
		}
		for (int i = WideFirstIndex; i <= WideLastIndex; i++) {
			FTransform RapidTransform;
			SetAndGetRapidShotAngle(InDirection, FVector(0.8, 0.8, 0.8), i, RapidTransform);
			ABulletBase* SpawnBullet = GetWorld()->SpawnActor<ABulletBase>(RapidShotClass, RapidTransform);
			ReduceBulletCount(1);
		}
	}
}

void ATMMAPlayerBase::ShotHoming(FVector InDirection)
{
	if (HomingShotClass != nullptr) {
		FVector HomingShotScale = FVector(1.0, 1.0, 1.0);
		switch (ShotLevel)
		{
			case 2:
				HomingShotScale = FVector(1.5, 1.5, 1.5);
				break;
			case 3:
				HomingShotScale = FVector(2.0, 2.0, 2.0);
				break;
			default:
				break;
		}
		FTransform RapidTransform;
		SetAndGetShotAngle(InDirection, HomingShotScale, RapidTransform);
		GetWorld()->SpawnActor<ABulletBase>(HomingShotClass, RapidTransform);
		ReduceBulletCount(1);
	}
}

void ATMMAPlayerBase::ShotFire(FVector InDirection)
{
	if (FireShotClass != nullptr) {
		FTransform RapidTransform;
		SetAndGetShotAngle(InDirection, FVector(1.0, 1.0, 1.0), RapidTransform);
		GetWorld()->SpawnActor<ABulletBase>(FireShotClass, RapidTransform);
	}
}

void ATMMAPlayerBase::ShotGrenade(FVector InDirection)
{
	if (GrenadeShotClass != nullptr) {
		FTransform RapidTransform;
		SetAndGetShotAngle(InDirection, FVector(1.0, 1.0, 1.0), RapidTransform);
		GetWorld()->SpawnActor<ABulletBase>(GrenadeShotClass, RapidTransform);
		ReduceBulletCount(3);
		InitShotTime();
		while (ShotTime < 0.5) {
			AddShotTime(0.01);
		}
		ShotTime = 0.5;
	}
}

void ATMMAPlayerBase::ShotLaser(FVector InDirection)
{
	if (LaserShotClass != nullptr) {
		FVector LaserShotScale = FVector(1.0, 1.0, 1.0);
		switch (ShotLevel)
		{
		case 2:
			LaserShotScale = FVector(1.5, 1.5, 1.0);
			break;
		case 3:
			LaserShotScale = FVector(2.0, 2.0, 1.0);
			break;
		default:
			break;
		}

		FTransform RapidTransform;
		SetAndGetShotAngle(InDirection, LaserShotScale, RapidTransform);
		ABulletBase* SpawnLaser = GetWorld()->SpawnActor<ABulletBase>(LaserShotClass, RapidTransform);
		if (IsValid(SpawnLaser)) {
			SpawnLaser->AddActorLocalRotation(FRotator(0.0, -90.0, 90.0));
		}
	}
}


void ATMMAPlayerBase::ShotMissile(float YAxis)
{
	if (PlayerMissile != nullptr) {
//		if (GameInstance) {
			FVector ShotVector = FVector(0.0, YAxis, 0.0);
			FTransform ShotTransform;
			SetAndGetShotAngle(ShotVector, FVector(1.0, 1.0, 1.0), ShotTransform);
			ABulletBase* SpawnedPlayerMissile = GetWorld()->SpawnActor<ABulletBase>(PlayerMissile, ShotTransform);
			if (IsValid(SpawnedPlayerMissile) == true) {
				SpawnedPlayerMissile->AddActorWorldRotation(FRotator(90.0, 0.0, 0.0));
			}
//		}
	}
}

void ATMMAPlayerBase::ShotLevelUp()
{
	int AfterShotLevel = ShotLevel + 1;
	if (AfterShotLevel >= 4) {
		AfterShotLevel = 1;
	}
	SetShotLevel(AfterShotLevel);
}

void ATMMAPlayerBase::SetShotLevel(int InShotLevel)
{
	ShotLevel = InShotLevel;
}

void ATMMAPlayerBase::SetAndGetShotAngle(FVector Direction, FVector BulletScale, FTransform& GetTransform)
{
	if (Direction.Size() > 0) {
		BulletAim = Direction;
	}
	FRotator BulletAimRotator = BulletAim.Rotation();
	BulletAimRotator.Roll = 0.0;
	FVector RoVector = BulletAimRotator.RotateVector(BulletSet);
	GetTransform = UKismetMathLibrary::MakeTransform(this->GetActorLocation() + RoVector, BulletAimRotator, BulletScale);
}

void ATMMAPlayerBase::SetAndGetRapidShotAngle(FVector Direction, FVector BulletScale, int CombineIndex, FTransform& GetTransform)
{
	if (Direction.Size() > 0) {
		BulletAim = Direction;
	}
	FRotator BulletAimRotator = BulletAim.Rotation();
	BulletAimRotator.Roll = 0.0;
	BulletAimRotator += FRotator(CombineIndex * 10.0, 0.0, 0.0);
	FVector RoVector = BulletAimRotator.RotateVector(BulletSet);
	GetTransform = UKismetMathLibrary::MakeTransform(this->GetActorLocation() + RoVector, BulletAimRotator, BulletScale);
}

void ATMMAPlayerBase::SetPlayerMode(EPlayerMode InPlayerMode)
{
	PlayerMode = InPlayerMode;
}

void ATMMAPlayerBase::DamageAndMissCheck(int DamageLife, UCharacterMovementComponent* InCharacterComponent, UBoxComponent* InBoxComponent)
{
	if (IsInvinsible == false) {
		// 無敵じゃないときに処理を実行
		DamagePlayerLife(DamageLife); // ダメージ処理
		if (PlayerHp <= 0) {
			// ライフが0ならミス処理実行
			// プレイヤーキャラの判定を無くし、操作不能にする.
			InBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			InCharacterComponent->DisableMovement();
			IsAbleControll = false;
			// ミスサウンドとパーティクル生成
			UTMMAActorLibrary::SpawnSeAndParticle(this, DefeatedParticle, DefeatedSound, this->GetActorLocation(), FVector(1.0, 1.0, 1.0));
			// 無敵状態にする
			IsInvinsible = true;
			// ミス処理を実行.
			MainGameMode->PlayerMiss(EPlayerMissType::Defeated);
		}
		else {
			// まだライフが残っているなら無敵処理とボイス生成
			UGameplayStatics::PlaySound2D(this->GetWorld(), DamageVoice);
			SetInvinsible();

		}
	}
}


void ATMMAPlayerBase::AddPlayerLife(int AddLife)
{
	PlayerHp += AddLife;
}

void ATMMAPlayerBase::DamagePlayerLife(int DamageLife)
{
	if (IsInvinsible == false) {
		AddPlayerLife(-DamageLife);
	}
}

void ATMMAPlayerBase::PlayerMissFunc(UParticleSystem* InMissParticle, USoundBase* InMissSound, UCharacterMovementComponent* InCharacterMovement)
{
	UTMMAActorLibrary::SpawnSeAndParticle(this, InMissParticle, InMissSound, this->GetActorLocation(), FVector(1.0, 1.0, 1.0));
	InCharacterMovement->DisableMovement();
	SetIsInvinsible(true);
	SetIsAbleControll(false);
}

void ATMMAPlayerBase::StageClearLifeRegain(int AddLife)
{
	int RegainLife = AddLife;
	if ((PlayerHp + AddLife) > 100) {
		if (PlayerHp < 100) {
			RegainLife = 100 - PlayerHp;
		}
		else {
			RegainLife = 0;
		}
	}
	AddPlayerLife(RegainLife);
}

void ATMMAPlayerBase::SetIsAbleBurst(bool InIsAbleBurst)
{
	IsAbleBurst = InIsAbleBurst;
}

void ATMMAPlayerBase::SetPlayerLife(int InLife)
{
	PlayerHp = InLife;
}

void ATMMAPlayerBase::SpawnBurst()
{
	if (BurstCount > 0 && IsAbleBurst == true) {
		GetCharacterMovement()->MaxWalkSpeed = 1200;
		IsAbleBurst = false;
		if (BurstBomb != nullptr) {
			GetWorld()->SpawnActor<AActor>(BurstBomb, this->GetActorTransform());
			SetInvinsible();
			BurstCount--;
		}
	}
}

void ATMMAPlayerBase::BurstOut()
{
	GetCharacterMovement()->MaxWalkSpeed = 800;
	IsAbleBurst = true;
}

void ATMMAPlayerBase::AddBurstCount() {
	BurstCount++;
}
void ATMMAPlayerBase::SetBurstCount(int InBurstCount)
{
	BurstCount = InBurstCount;
}

void ATMMAPlayerBase::SetIsMissileOfAction(bool InIsMissileOfAction)
{
	IsMissileOfAction = InIsMissileOfAction;
}

void ATMMAPlayerBase::SetMissileMode()
{
	ECurrentStage CurrentStage = MainGameMode->GetCurrentStage();
	if (CurrentStage == ECurrentStage::Stage6 || CurrentStage == ECurrentStage::Stage7) {
		IsMissileOfAction = true;
	}
	else {
		IsMissileOfAction = false;
	}
}

void ATMMAPlayerBase::AddShotButtonPussingTime()
{
	ShotButtonPussingTime += 0.1;
}

void ATMMAPlayerBase::InitShotButtonPussingTime()
{
	ShotButtonPussingTime = 0.0;
}

void ATMMAPlayerBase::SetIsInvinsible(bool InIsInvinsible)
{
	IsInvinsible = InIsInvinsible;
}

void ATMMAPlayerBase::SetBulletCount(int InBulletCount)
{
	BulletCount = InBulletCount;
}

void ATMMAPlayerBase::ReduceBulletCount(int InReduceBulletCount)
{
	BulletCount -= InReduceBulletCount;
}

void ATMMAPlayerBase::ReloadBulletCount(int InReloadBulletCount)
{
	BulletCount += InReloadBulletCount;
	if (BulletCount > BulletLimit) {
		BulletCount = BulletLimit;
	}
}

void ATMMAPlayerBase::SetIsAbleSwordAttack(bool InIsAbleSwordAttack) {
	IsAbleSwordAttack = InIsAbleSwordAttack;
}

void ATMMAPlayerBase::SetBulletAim(FVector InBulletAim) {
	BulletAim = InBulletAim;
}

void ATMMAPlayerBase::SetBulletSet(FVector InBulletSet) {
	BulletSet = InBulletSet;
}

void ATMMAPlayerBase::SetShotType(EShotType InShotType)
{
	ShotType = InShotType;
}

void ATMMAPlayerBase::SetShotTypeIndex(int InShotTypeIndex)
{
	ShotTypeIndex = InShotTypeIndex;
}

void ATMMAPlayerBase::InitShotTime()
{
	ShotTime = 0.0f;
}

void ATMMAPlayerBase::AddShotTime(float InShotTime) {
	ShotTime += InShotTime;
}

void ATMMAPlayerBase::SetInvinsible()
{
	// 時間経過して解除もできるようにしたい。
	if (IsInvinsible == false) {
		SetIsInvinsible(true);
		if (InvinsibleBarrier != nullptr) {
			GetWorld()->SpawnActor<AActor>(InvinsibleBarrier, this->GetActorTransform());
		}
		// 時間経過で解除.
		//Tickに任せてみる

		FTimerHandle handle;
		FTimerManager& TimerManager = GetWorldTimerManager();

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("SetIsInvinsible"), false);
		TimerManager.SetTimer(handle, TimerDelegate, MaxInvinsibleTime, false);

	}
}

void ATMMAPlayerBase::SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode)
{
	MainGameMode = InMainGameMode;
}

void ATMMAPlayerBase::SetMainGameState(ATMMAGameStateBase* InMainGameState)
{
	MainGameState = InMainGameState;
}

void ATMMAPlayerBase::SetMissVoiceBySoft()
{
	DefeatMissVoice = SoftDefeatMissVoice.LoadSynchronous();
	DropOutMissVoice = SoftDropOutMissVoice.LoadSynchronous();
}

void ATMMAPlayerBase::SetDamageVoiceBySoft()
{
	DamageVoice = SoftDamageVoice.LoadSynchronous();
}

void ATMMAPlayerBase::SetDefeatedSoundAndParticleBySoft()
{
	DefeatedSound = SoftDefeatedSound.LoadSynchronous();
	DefeatedParticle = SoftDefeatedParticle.LoadSynchronous();
}

void ATMMAPlayerBase::SetSoundAndParticleAll()
{
	SetMissVoiceBySoft();
	SetDamageVoiceBySoft();
	SetDefeatedSoundAndParticleBySoft();
}


void ATMMAPlayerBase::SetSwordTargetActor(AActor* InActor)
{
	if (InActor->ActorHasTag("Enemy") || (InActor->ActorHasTag("CrushObject"))) {
		SwordTargetActor = InActor;
	}
}

void ATMMAPlayerBase::CheckAbleSword(float PlusDistanceY, float MinusDistanceY, float PlusDistanceZ, float MinusDistanceZ)
{
	SetIsAbleSwordAttack(false);
	if (SwordTargetActor != nullptr) {
		if (IsValid(SwordTargetActor) == true) {
			bool IsTargetSightY = UTMMAActorLibrary::GetIsInDistanceY(this, SwordTargetActor, PlusDistanceY, MinusDistanceY);
			bool IsTargetSightZ = UTMMAActorLibrary::GetIsInDistanceZ(this, SwordTargetActor, PlusDistanceZ, MinusDistanceZ);
			if (IsTargetSightY == true && IsTargetSightZ) {
				SetIsAbleSwordAttack(true);
			}
		}
	}
}

void ATMMAPlayerBase::SetSwordAttackSwitch(bool InSwordAttackSwitch)
{
	SwordAttackSwitch = InSwordAttackSwitch;
}

void ATMMAPlayerBase::AddSwordWaitTime()
{
	if (SwordAttackSwitch == true)
	{
		SwordWaitTime += 0.1f;
		if (SwordWaitTime >= MaxSwordWaitTime) {
			SwordWaitTime = 0.0f;
			SwordAttackSwitch = false;
		}
	}
}

/*---------------------------
 * デバッグ用処理
 *--------------------------*/
// ショット切り替え
void ATMMAPlayerBase::ChangeShotForDebug()
{
	ShotTypeIndex++;
	if (ShotTypeIndex >= 5) {
		ShotTypeIndex = 0;
	}
	switch (ShotTypeIndex)
	{
		case 0:
			ShotType = EShotType::Rapid;
			break;
		case 1:
			ShotType = EShotType::Homing;
			break;
		case 2:
			ShotType = EShotType::Fire;
			break;
		case 3:
			ShotType = EShotType::Grenade;
			break;
		case 4:
			ShotType = EShotType::Laser;
			break;
		default:
			break;
	}
}

