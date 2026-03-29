// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMAGeneratorBase.h"



// Sets default values
ATMMAGeneratorBase::ATMMAGeneratorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMMAGeneratorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMMAGeneratorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMMAGeneratorBase::InitGeneratorActorByTable(TArray<FName> RowNameList)
{
	if (DataTable != nullptr) {
		// TODO::データテーブルからRowNameを持ってくる手段が知りたいし、それで引数無しで格納できるようにしたい。
		for (int i = 0; i < RowNameList.Num(); i++) {
			auto GeneratorRecord = DataTable->FindRow<FGeneratorTableRow>(RowNameList[i], "");
			if (GeneratorRecord != nullptr) {
				//GenerateActorArray[i] = GeneratorRecord->SpawnClass;
			}
		}
	}
}

void ATMMAGeneratorBase::SpawnActor(FVector Location, FRotator Rotation, FVector Scale,  bool UnlimitedFlag, AActor*& SActor)
{
	if (IsValid(TargetActor)) {
		FTransform ActorTransform = UKismetMathLibrary::MakeTransform(Location, Rotation, Scale);
		if (UnlimitedFlag) {
			// 無限生成
			SActor = GetWorld()->SpawnActor<AActor>(TargetActor, ActorTransform);
		}
		else {
			if (SpawnCount < LimitCount){
				// 指定数分生成
				SActor = GetWorld()->SpawnActor<AActor>(TargetActor, ActorTransform);
				SpawnCount++;
				if (SpawnCount == LimitCount) {
					// 最後のアクタをトリガー対象アクタにする.
					SetTriggerActor(SActor);
				}
			}
			else {
				SpawnCount = 0;
				SActor = nullptr;
			}
		}
	}
}

void ATMMAGeneratorBase::SetLimitCount(int InLimitCount)
{
	LimitCount = InLimitCount;
}

void ATMMAGeneratorBase::SetSpawnCount(int InSpawnCount)
{
	SpawnCount = InSpawnCount;
}

void ATMMAGeneratorBase::InitSpawnCount()
{
	SetSpawnCount(0);
}

void ATMMAGeneratorBase::SwitchGeneratorIndex(int InLimitIndex)
{
	int LimitIndex = InLimitIndex;
	// 空のインデックス呼び出してしまう可能性あるので、指定最大値をGenerateActorArrayにしておく.
	if (InLimitIndex > sizeof(GenerateActorArray)) {
		LimitIndex = sizeof(GenerateActorArray);
	}
	GeneratorIndex++;
	if (GeneratorIndex > LimitIndex) {
		GeneratorIndex = 0;
	}
}

void ATMMAGeneratorBase::SetGeneratorIndex(int InGeneratorIndex) {
	GeneratorIndex = InGeneratorIndex;
}

void ATMMAGeneratorBase::SpawnGenerateActorArray(int ArrayIndex, FVector Location, FRotator Rotation, FVector Scale, AActor*& SActor)
{	
	if (IsValid(GenerateActorArray[ArrayIndex])) {
		TSubclassOf<AActor> GenerateActor = GenerateActorArray[ArrayIndex];
		FTransform ActorTransform = UKismetMathLibrary::MakeTransform(Location, Rotation, Scale);
		if (SpawnCount <= LimitCount) {
			SActor = GetWorld()->SpawnActor<AActor>(GenerateActor, ActorTransform);
;			SpawnCount++;
			if (SpawnCount == LimitCount) {
				SetTriggerActor(SActor);
			}
		}
		else {
			SpawnCount = 0;
			SActor = nullptr;
		}

	}
}

// BeginPlay用の初期設定
void ATMMAGeneratorBase::InitSingleStatus(TSubclassOf<AActor> InTargetActor, int InLimitCount)
{
	TargetActor = InTargetActor;
	LimitCount = InLimitCount;
}

// BeginPlay用の初期設定

void ATMMAGeneratorBase::InitGenerateStatus(TArray<TSubclassOf<AActor>> InGenerateActorArray, int InGeneratorIndex)
{
	GenerateActorArray = InGenerateActorArray;
	GeneratorIndex = InGeneratorIndex;
}

void ATMMAGeneratorBase::SetTriggerActor(AActor* InTriggerActor)
{
	TriggerActor = InTriggerActor;
}

void ATMMAGeneratorBase::SetSpawnVector(FVector InSpawnVector)
{
	SpawnVector = InSpawnVector;
}

void ATMMAGeneratorBase::InitDestroyCount() 
{
	DestroyCount = 0;
}

void ATMMAGeneratorBase::AddDestroyCount() {
	DestroyCount++;
}