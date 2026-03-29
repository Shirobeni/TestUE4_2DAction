
// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMADemoGameBase.h"
#include "TestMyMakeAction/Object/TMMACustomWorldSettings.h"
#include "TestMyMakeAction/Controller/TMMADemoPlayerController.h"
#include "TestMyMakeAction/TMMAGameInstanceBase.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ATMMADemoGameBase::BeginPlay()
{
	Super::BeginPlay();
	// あらかじめ、プレイヤー関連ステータスの初期化
	if (UTMMAGameInstanceBase* GameInstanceBase = Cast<UTMMAGameInstanceBase>(GetGameInstance())) {
		GameInstanceBase->InitGameStatus();
	}
	// 操作用ポーン生成
	TSubclassOf<ATMMAAtructDemoControllPawn> AtructPawnClass = SoftAtractPawnClass.LoadSynchronous();
	if (!AtructPawnClass) return;
	FTransform Transform = UKismetMathLibrary::MakeTransform(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	ATMMAAtructDemoControllPawn* SpawnedAtructPawn =  GetWorld()->SpawnActor<ATMMAAtructDemoControllPawn>(AtructPawnClass, Transform);
	if (!SpawnedAtructPawn) return;
	AtractPawn = SpawnedAtructPawn;
	// 操作用ポーンの設定
	AGameStateBase* GameStateBase = GetGameState<AGameStateBase>();
	APlayerState* PlayerState = GameStateBase->PlayerArray[0];
	if (!PlayerState) return;
	APlayerController* PlayerControllerBase = Cast<APlayerController>(PlayerState->GetOwner());
	if (!PlayerControllerBase) return;
	if (ATMMADemoPlayerController* DemoPlayerController = Cast<ATMMADemoPlayerController>(PlayerControllerBase)) {
		DemoPlayerController->SetControllPawn(SpawnedAtructPawn);
		DemoPlayerController->CreateAtructDemoWidget();
		// 表示ウィジェット形式設定
		// ワールドセッティングの取得
		AWorldSettings* WorldSettings = GetWorldSettings();
		if (WorldSettings == nullptr) return;
		if (ATMMACustomWorldSettings* CustomWorldSettings = Cast<ATMMACustomWorldSettings>(WorldSettings)) {
			// どのレベルタイプかで表示形式を変える
			DemoPlayerController->GetAtructDemoWidget()->ChangeWidgetCanvasMode(CustomWorldSettings->LevelMode);
		}
	}
	IsOpenLevelDoOnce = false;
	MaxViewTime = MaxViewTimeList[AtructType];
	LoadDemoLevel();
}

void ATMMADemoGameBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (IsCreditInserted) {
		ViewTime = 0.0f;
	} else {
		ViewTime += 0.01f;
		if (ViewTime >= MaxViewTime && !IsOpenLevelDoOnce) {
			IsOpenLevelDoOnce = true;
			OpenNextDemoLevel();
		}
	}
}


void ATMMADemoGameBase::LoadDemoLevel()
{
	FString LevelString = "";
	if (AtructType == EAtructType::ReadyCredit) {
		LevelString = "stage1";
	}
	else {
		// クレジット投入後のレベルはあらかじめ読み込んでおく.
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(GetWorld(), FName(TEXT("ReadyStart")), false, true, LatentInfo);
		switch (AtructType) {
		default:
			break;
		case EAtructType::Title:
			// TODO::デモ画面用レベルが出来たら変更.
			LevelString = "AtructRanking";
			break;
		case EAtructType::Ranking:
			LevelString = "AtructTitle";
			break;
		}
	}
	if (LevelString != "") {
		FName LevelName = FName(LevelString);
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(GetWorld(), LevelName, false, true, LatentInfo);
	}
}

void ATMMADemoGameBase::OpenNextDemoLevel()
{
	FString LevelString = "";
	switch (AtructType) {
		default:
			break;
		case EAtructType::Title:
			// TODO::デモ画面用レベルが出来たら変更.
			LevelString = "AtructRanking";
			break;
		case EAtructType::Ranking:
			LevelString = "AtructTitle";
			break;
	}
	if (LevelString != "") {
		FName LevelName = FName(LevelString);
		FLatentActionInfo LatentInfo;
		UGameplayStatics::OpenLevel(GetWorld(), LevelName, false);
	}
}

