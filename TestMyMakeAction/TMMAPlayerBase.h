// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Rotator.h"
#include "Library/TMMAActorLibrary.h"
#include "TMMAPlayerInterfaceBase.h"
#include "TMMAPlayerCameraBase.h"
#include "TMMAPlayerBase.generated.h"

#define DEFINE_MAX_INVINSIBLE_TIME 2.0f;

UENUM(BlueprintType)
enum class EShotType : uint8
{
	Rapid UMETA(DisplayName = "Rapid"),
	Homing UMETA(DisplayName = "Homing"),
	Fire UMETA(DisplayName = "Fire"),
	Grenade UMETA(DisplayName = "Grenade"),
	Laser UMETA(DisplayName = "Laser")
};

UENUM(BlueprintType)
enum class EPlayerMode : uint8
{
	Action UMETA(DisplayName = "Action"),
	Shooting UMETA(DisplayName = "Homing"),
};

UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Shot UMETA(DisplayName = "Shot"),
	Sword UMETA(DisplayName = "Sword"),
	Death UMETA(DisplayName = "Death")
};


UCLASS()
class TESTMYMAKEACTION_API ATMMAPlayerBase : public ACharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATMMAPlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	ATMMAPlayerCameraBase* GetPlayerCamera() { return PlayerCamera; }
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// スポーン時のインスタンスからのステータス引継ぎ
	UFUNCTION(BlueprintCallable)
	void TakeOverPlayerStatusByInstance(UTMMAGameInstanceBase* InGameInstance);


	// 各ショットのソフト参照クラスをクラス化。
	UFUNCTION(BlueprintCallable)
	void SetShotClassBySoft();

	// コントロール可能フラグ
	UFUNCTION(BlueprintCallable)
	void SetIsAbleControll(bool InIsAbleControll);

	UFUNCTION(BlueprintPure)
	bool GetIsAbleControll() {
		return IsAbleControll;
	}

	// ショットボタン押しているかのフラグ
	UFUNCTION(BlueprintCallable)
	void SetIsPussingShotButton(bool InIsPussingShotButton);

	UFUNCTION(BlueprintPure)
	const bool GetIsPussingShotButton() const
	{
		return IsPussingShotButton;
	}

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void SetPlayerCamera(ATMMAPlayerCameraBase* Camera);

	UFUNCTION(BlueprintCallable)
		void MoveLeft(FVector RunSpeed, float Value);

	UFUNCTION(BlueprintCallable)
		void MoveRignt(FVector RunSpeed, float Value);

	UFUNCTION(BlueprintCallable)
		void MoveUp(FVector RunSpeed, float Value);

	UFUNCTION(BlueprintCallable)
		void MoveDown(FVector RunSpeed, float Value);


	// 全ての移動共通化
	UFUNCTION(BlueprintCallable)
		void MoveCharacter(FVector RunSpeed, float Value);

	UFUNCTION(BlueprintCallable)
		void ShotRapid(FVector InDirection);

	UFUNCTION(BlueprintCallable)
		void ShotHoming(FVector InDirection);

	UFUNCTION(BlueprintCallable)
		void ShotFire(FVector InDirection);

	UFUNCTION(BlueprintCallable)
		void ShotGrenade(FVector InDirection);

	UFUNCTION(BlueprintCallable)
		void ShotLaser(FVector InDirection);

	UFUNCTION(BlueprintCallable)
		void Shot(float VectorY, float VectorZ);

	UFUNCTION(BlueprintCallable)
		void ShotMissile(float YAxis);


	UFUNCTION(BlueprintCallable)
		void ShotLevelUp();

	UFUNCTION(BlueprintCallable)
		void SetShotLevel(int InShotLevel);

	UFUNCTION(BlueprintPure)
		const int GetShotLevel() const
	{
		return ShotLevel;
	}


	UFUNCTION(BlueprintPure)
		void SetAndGetShotAngle(FVector Direction, FVector BulletScale, FTransform& GetTransform);

	// RapidShot専用
	UFUNCTION(BlueprintPure)
		void SetAndGetRapidShotAngle(FVector Direction, FVector BulletScale, int CombineIndex, FTransform& GetTransform);

	UFUNCTION(BlueprintCallable)
		void DamageAndMissCheck(int DamageLife, UCharacterMovementComponent* InCharacterComponent, UBoxComponent* InBoxComponent);

	UFUNCTION(BlueprintCallable)
		void AddPlayerLife(int AddLife);

	UFUNCTION(BlueprintCallable)
	void DamagePlayerLife(int DamageLife);

	UFUNCTION(BlueprintCallable)
	void PlayerMissFunc(UParticleSystem* InMissParticle, USoundBase* InMissSound, UCharacterMovementComponent* InCharacterMovement);

	UFUNCTION(BlueprintCallable)
	void StageClearLifeRegain(int AddLife);

	UFUNCTION(BlueprintPure)
	const int GetPlayerLife() const
	{
		return PlayerHp;
	}

	UFUNCTION(BlueprintCallable)
		void SetPlayerLife(int InLife);


	UFUNCTION(BlueprintCallable)
	void SetIsMissileOfAction(bool InIsMissileOfAction);

	UFUNCTION(BlueprintPure)
	const bool GetIsMissileOfAction() const
	{
		return IsMissileOfAction;
	}

	UFUNCTION(BlueprintCallable)
		void SetMissileMode();

	UFUNCTION(BlueprintCallable)
		void SetIsAbleBurst(bool InIsAbleBurst);

	UFUNCTION(BlueprintPure)
	const bool GetIsAbleBurst() const
	{
		return IsAbleBurst;
	}

	UFUNCTION(BlueprintCallable)
	void SpawnBurst();

	UFUNCTION(BlueprintCallable)
	void BurstOut();


	UFUNCTION(BlueprintCallable)
	void AddBurstCount();

	UFUNCTION(BlueprintCallable)
	void SetBurstCount(int InBurstCount);

	UFUNCTION(BlueprintPure)
	const int GetBurstCount() const
	{
		return BurstCount;
	}

	UFUNCTION(BlueprintCallable)
	void InitShotButtonPussingTime();

	UFUNCTION(BlueprintCallable)
	void AddShotButtonPussingTime();

	UFUNCTION(BlueprintPure)
	const float GetShotButtonPussingTime() const
	{
		return ShotButtonPussingTime;
	}

	UFUNCTION(BlueprintCallable)
		void SetIsInvinsible(bool InIsInvinsible);

	UFUNCTION(BlueprintPure)
		const bool GetIsInvinsible() const
	{
		return IsInvinsible;
	}

	UFUNCTION(BlueprintCallable)
		void SetBulletCount(int InBulletCount);

	UFUNCTION(BlueprintCallable)
		void ReduceBulletCount(int InReduceBulletCount);

	UFUNCTION(BlueprintCallable)
		void ReloadBulletCount(int InReloadBulletCount);

	UFUNCTION(BlueprintPure)
	const int GetBulletLimit() const
	{
		return BulletLimit;
	}

	UFUNCTION(BlueprintPure)
		const int GetBulletCount() const
	{
		return BulletCount;
	}

	UFUNCTION(BlueprintCallable)
		void SetIsAbleSwordAttack(bool InIsAbleSwordAttack);

	UFUNCTION(BlueprintPure)
		const bool GetIsAbleSwordAttack() const
	{
		return IsAbleSwordAttack;
	}

	UFUNCTION(BlueprintCallable)
		void SetBulletAim(FVector InBulletAim);

	UFUNCTION(BlueprintPure)
	FVector GetBulletAim() {
		return BulletAim;
	}

	UFUNCTION(BlueprintCallable)
		void SetBulletSet(FVector InBulletSet);

	UFUNCTION(BlueprintPure)
	FVector GetBulletSet() {
		return BulletSet;
	}


	UFUNCTION(BlueprintCallable)
		void SetShotType(EShotType InShotType);

	UFUNCTION(BlueprintPure)
	EShotType GetShotType() {
		return ShotType;
	}

	UFUNCTION(BlueprintCallable)
	void SetPlayerMode(EPlayerMode InPlayerMode);

	UFUNCTION(BlueprintPure)
	EPlayerMode GetPlayerMode() const
	{
		return PlayerMode;
	}

	UFUNCTION(BlueprintCallable)
		void SetShotTypeIndex(int InShotTypeIndex);

	UFUNCTION(BlueprintPure)
		const int GetShotTypeIndex() 
	{
		return ShotTypeIndex;
	}

	UFUNCTION(BlueprintCallable)
		void InitShotTime();

	UFUNCTION(BlueprintCallable)
		void AddShotTime(float InShotTime);

	UFUNCTION(BlueprintPure)
		const float GetShotTime() const
	{
		return ShotTime;
	}

	UFUNCTION(BlueprintCallable)
	void SetInvinsible();

	UFUNCTION(BlueprintCallable)
	const float GetMaxInvinsibleTime() const
	{
		return MaxInvinsibleTime;
	}

	UFUNCTION(BlueprintCallable)
	void SetMainGameMode(ATestMyMakeActionGameModeBase* InMainGameMode);

	UFUNCTION(BlueprintPure)
	ATestMyMakeActionGameModeBase* GetMainGameMode() const {
		return MainGameMode;
	}

	UFUNCTION(BlueprintCallable)
	void SetMainGameState(ATMMAGameStateBase* InMainGameState);

	UFUNCTION(BlueprintPure)
	ATMMAGameStateBase* GetMainGameState() const
	{
		return MainGameState;
	}

	USoundBase* GetDefeatMissVoice() const
	{
		return DefeatMissVoice;
	}

	USoundBase* GetDropOutMissVoice() const
	{
		return DropOutMissVoice;
	}

	void SetDamageVoiceBySoft();

	void SetMissVoiceBySoft();

	void SetDefeatedSoundAndParticleBySoft();

	UFUNCTION(BlueprintCallable)
	void SetSwordTargetActor(AActor* InActor);

	UFUNCTION(BlueprintCallable)
	void SetSoundAndParticleAll();

	UFUNCTION(BlueprintCallable)
	void CheckAbleSword(float PlusDistanceY, float MinusDistanceY, float PlusDistanceZ, float MinusDistanceZ);

	UFUNCTION(BlueprintCallable)
	void SetSwordAttackSwitch(bool InSwordAttackSwitch);

	UFUNCTION(BlueprintPure)
	const bool GetSwordAttackSwitch() const
	{
		return SwordAttackSwitch;
	}

	void AddSwordWaitTime();

	UFUNCTION(BlueprintPure)
	const float GetMaxSwordWaitTime() const
	{
		return MaxSwordWaitTime;
	}

	// デバッグ用処理
	// ショット切り替え
	UFUNCTION(BlueprintCallable)
	void ChangeShotForDebug();

	// アニメーション関連
	void SetAnimMontageListBySoft();

	void PlayAnimMontageByAnimType(EPlayerAnimType InAnimType, float InLateTime);

protected:
	ATMMAPlayerCameraBase* PlayerCamera;

	UPROPERTY()
	AActor* SwordTargetActor = nullptr;

	bool IsPussingShotButton = false;

public:
		int ShotLevel = 1;

		int BulletCount = 15;

		int BulletLimit = 15;

		float ShotButtonPussingTime = 0.0;

		int PlayerHp = 100;

		int PlayerLeft = 2;

		int BurstCount = 3;

		float MaxInvinsibleTime = DEFINE_MAX_INVINSIBLE_TIME;

		bool IsAbleBurst = false;

		bool IsInvinsible = false;

		bool IsAbleSwordAttack = false;

		bool SwordAttackSwitch = false;

		float SwordWaitTime = 0.0f;

		float MaxSwordWaitTime = 0.4f;

		// ミスボイス
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSound")
		TSoftObjectPtr<USoundBase> SoftDefeatMissVoice;

		USoundBase* DefeatMissVoice;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSound")
		TSoftObjectPtr<USoundBase> SoftDropOutMissVoice;

		USoundBase* DropOutMissVoice;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStatus")
		EShotType ShotType = EShotType::Rapid;
		
		EPlayerMode PlayerMode = EPlayerMode::Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStatus")
		float ShotTime = 0.0f;
	// 恐らくデバッグ用
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStatus")
		int ShotTypeIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotVector")
		FVector BulletSet = FVector(0.0, 0.0, 0.0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShotVector")
		FVector BulletAim = FVector(0.0, 1.0, 0.0);

		bool IsMissileOfAction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BurstActor")
		TSubclassOf<AActor> BurstBomb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InvinsibleActor")
	TSubclassOf<AActor> InvinsibleBarrier;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<class ABulletBase> RapidShotSoftClass = nullptr;

	TSubclassOf<class ABulletBase> RapidShotClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<class ABulletBase> HomingShotSoftClass = nullptr;

	TSubclassOf<class ABulletBase> HomingShotClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<class ABulletBase> FireShotSoftClass = nullptr;

	TSubclassOf<class ABulletBase> FireShotClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<class ABulletBase> GrenadeShotSoftClass = nullptr;

	TSubclassOf<class ABulletBase> GrenadeShotClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<class ABulletBase> LaserShotSoftClass = nullptr;

	TSubclassOf<class ABulletBase> LaserShotClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<class ABulletBase> PlayerMissileSoftClass = nullptr;

	TSubclassOf<class ABulletBase> PlayerMissile = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<USoundBase> SoftDamageVoice = nullptr;

	USoundBase* DamageVoice = nullptr;

	UPROPERTY(EditDefaultsOnly)
		TSoftObjectPtr<USoundBase>	SoftDefeatedSound;

	USoundBase* DefeatedSound = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UParticleSystem> SoftDefeatedParticle;

	UParticleSystem* DefeatedParticle = nullptr;

	// プレイヤーカメラ用クラス
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<ATMMAPlayerCameraBase> SoftPlayerCameraClass;

	ATestMyMakeActionGameModeBase* MainGameMode;

	ATMMAGameStateBase* MainGameState;

	bool IsAbleControll = false;

	// アニメーション関連
	UPROPERTY(EditAnyWhere)
	TMap<EPlayerAnimType, TSoftObjectPtr<UAnimMontage>> SoftAnimMontageList;


protected:
	TMap<EPlayerAnimType, UAnimMontage*> AnimMontageList;
};
