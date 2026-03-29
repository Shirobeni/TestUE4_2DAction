// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMATitleGameMode.h"
#include "TestMyMakeAction/TMMAGameInstanceBase.h"
#include "TestMyMakeAction/Controller/TMMATitlePlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"


void ATMMATitleGameMode::BeginPlay() 
{
	Super::BeginPlay();
	UTMMAGameInstanceBase * GameInstanceBase = nullptr;
	if (UTMMAGameInstanceBase* CastedGameInstanceBase = Cast<UTMMAGameInstanceBase>(GetGameInstance())) {
		GameInstanceBase = CastedGameInstanceBase;
		GameInstanceBase->InitPlayerGameAndRankingStatus();
	}
	// 操作用ポーンの生成
	TSubclassOf<ATMMAWidgetControllPawn> WidgetControllPawnClass = SoftWidgetControllPawnClass.LoadSynchronous();
	if (!WidgetControllPawnClass) return;
	FTransform Transform = UKismetMathLibrary::MakeTransform(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	ATMMAWidgetControllPawn* SpawnedWidgetControllPawn = GetWorld()->SpawnActor<ATMMAWidgetControllPawn>(WidgetControllPawnClass, Transform);
	if (!SpawnedWidgetControllPawn) return;
	WidgetContorllPawn = SpawnedWidgetControllPawn;
	// 操作用ポーンの設定
	AGameStateBase* GameStateBase = GetGameState<AGameStateBase>();
	APlayerState* PlayerState = GameStateBase->PlayerArray[0];
	if (!PlayerState) return;
	APlayerController* PlayerControllerBase = Cast<APlayerController>(PlayerState->GetOwner());
	if (!PlayerControllerBase) return;
	if (ATMMATitlePlayerController* TitlePlayerController = Cast<ATMMATitlePlayerController>(PlayerControllerBase)) {
		TitlePlayerController->SetControllPawn(WidgetContorllPawn);
		TitlePlayerController->Possess(WidgetContorllPawn);
		TitlePlayerController->SetInputMode(FInputModeGameAndUI());
		// タイトル画面用ウィジェットの読み込み.
		TitlePlayerController->CreateTitleWidgetBySoftClass();
		WidgetContorllPawn->SetControllWidget(TitlePlayerController->GetTitleWidget());
	}
	// あらかじめアトラクトデモのタイトル画面は読み込んでおく. (ポートフォリオ向けはすぐにステージ1開始)
	FLatentActionInfo LatentInfo;
	if (GameInstanceBase && GameInstanceBase->BuildMode == EBuildMode::Portfolio) {
		UGameplayStatics::LoadStreamLevel(GetWorld(), FName(TEXT("/Game/map/Stage/stage1")), false, true, LatentInfo);
	}
	else {
		UGameplayStatics::LoadStreamLevel(GetWorld(), FName(TEXT("/Game/map/Demo/AtructTitle")), false, true, LatentInfo);
	}
}

void ATMMATitleGameMode::StartGame()
{
	// ゲームインスタンスの取得.
	UTMMAGameInstanceBase* GameInstanceBase = nullptr;
	if (UTMMAGameInstanceBase* CastedGameInstanceBase = Cast<UTMMAGameInstanceBase>(GetGameInstance())) {
		GameInstanceBase = CastedGameInstanceBase;
	}
	if (GameInstanceBase && GameInstanceBase->BuildMode == EBuildMode::Portfolio) {
		// ポートフォリオ向けの場合はステージ1へ遷移.
		UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/map/Stage/stage1")), false);
	} else {
		UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/map/Demo/AtructTitle")), false);
	}
}