// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMADestroiedObjectBase.h"

// Sets default values
ATMMADestroiedObjectBase::ATMMADestroiedObjectBase(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent*  SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent0"));
	if (SceneComponent) {
		RootComponent = SceneComponent;
	}

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent0"));
	if (ParticleSystemComponent) {
		ParticleSystemComponent->SetupAttachment(RootComponent);
		ParticleSystemComponent->SecondsBeforeInactive = 1.0f;
		ParticleSystemComponent->bAutoActivate;
	}

}


// Called when the game starts or when spawned
void ATMMADestroiedObjectBase::BeginPlay()
{
	AGameModeBase* GameModeBase = this->GetWorld()->GetAuthGameMode();
	if (ATestMyMakeActionGameModeBase* CastedGameMode = Cast<ATestMyMakeActionGameModeBase>(GameModeBase)) {
		GameMode = CastedGameMode;
	}
	Super::BeginPlay();
	
}

// Called every frame
void ATMMADestroiedObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMMADestroiedObjectBase::SetHp(int InHp)
{
	Hp = InHp;
}

void ATMMADestroiedObjectBase::SetScore(int InScore)
{
	Score = InScore;
}

void ATMMADestroiedObjectBase::SetParticle(UParticleSystem* InParticle)
{
	Particle = InParticle;
}

void ATMMADestroiedObjectBase::SetParticleScale(FVector InParticleScale)
{	

	FVector InScale = InParticleScale;
	//各ベクトルのデフォルトは1.0fに設定
	if (InScale.X <= 0.0) {
		InScale.X = DEFAULT_PARTICLE_FLOAT_SIZE;
	}
	if (InScale.Y <= 0.0) {
		InScale.Y = DEFAULT_PARTICLE_FLOAT_SIZE;
	}
	if (InScale.Z <= 0.0) {
		InScale.Z = DEFAULT_PARTICLE_FLOAT_SIZE;
	}
	ParticleScale = InParticleScale;

}

void ATMMADestroiedObjectBase::SetDestroySe(USoundBase* InDestroySe)
{
	DestroySe = InDestroySe;
}

void ATMMADestroiedObjectBase::DamageObject(int DamageParam, bool IsTimes)
{
	Hp -= DamageParam;
	if (Hp < 1) {
		if (GameMode != nullptr) {
			IGameModeInterface::Execute_AddEnemyScoreByDiff(GameMode, Score);
		}
		SpawnDestroyParticleAndSe();
		Destroy();
	}
}

bool ATMMADestroiedObjectBase::setObjectStatus(FName SetRowName, FClashObjectTableRow& EnemyParam)
{
	if (DataTable != nullptr) {
		FClashObjectTableRow* ObjectRecord = DataTable->FindRow<FClashObjectTableRow>(SetRowName, "");
		if (ObjectRecord != nullptr) {
			SetHp(ObjectRecord->Hp);
			SetScore(ObjectRecord->Score);
			UParticleSystem* ParticleOblect = ObjectRecord->SoftParticleData.LoadSynchronous();
			SetParticle(ParticleOblect);
			USoundBase* SeObject = ObjectRecord->SoftSe.LoadSynchronous();
			SetDestroySe(SeObject);
			SetParticleScale(ObjectRecord->ParticleScale);
			return true;

		}
	}
	return false;
}

void ATMMADestroiedObjectBase::SpawnDestroyParticleAndSe()
{
//	if ((Particle != nullptr) && (DestroySe != nullptr)) {
	if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(Particle) && UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(DestroySe)) {
		UTMMAActorLibrary::SpawnSeAndParticle(this, Particle, DestroySe, this->GetActorLocation(), ParticleScale);
	}
}

bool ATMMADestroiedObjectBase::ActiveExplotionParticle()
{
	if (ParticleSystemComponent) {
		ParticleSystemComponent->Activate();
		ParticleSystemComponent->SetTemplate(Particle);
		ParticleSystemComponent->SetEmitterEnable(NAME_None, true);

		return true;
	}
	return false;
}


