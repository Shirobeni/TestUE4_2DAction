// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestMyMakeActionGameModeBase.h"
#include "TestMyMakeAction/Controller/TMMAPlayerController.h"
#include "TMMALockCollisionBase.h"
#include "TMMAMaingameWidgetBase.h"
#include "Object/TMMACustomWorldSettings.h"
#include "TMMALockCollisionBase.h"

// 開始時の処理
void ATestMyMakeActionGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ATMMACustomWorldSettings* CustomWorldSettings = nullptr;
	UGameInstance* aGameInstanceBase = GetGameInstance<UGameInstance>();
	if (aGameInstanceBase == nullptr) return;
	if (UTMMAGameInstanceBase* CastedGameInstance = Cast<UTMMAGameInstanceBase>(aGameInstanceBase)) {
		MainGameInstance = CastedGameInstance;
		// ワールドセッティングの取得
		AWorldSettings* WorldSettings = GetWorldSettings();
		if (WorldSettings == nullptr) return;
		if (ATMMACustomWorldSettings* CastedCustomWorldSettings = Cast<ATMMACustomWorldSettings>(WorldSettings)) {
			CustomWorldSettings = CastedCustomWorldSettings;
			if (CustomWorldSettings->SoundDataAsset != nullptr) {
				MainGameInstance->SetSoudStructByDataAsset(CustomWorldSettings->SoundDataAsset);
			}
		}
	}
	// ゲームステートとプレイヤーステートの取得
	AGameStateBase* GameStateBase = GetGameState<AGameStateBase>();
	if (GameStateBase == nullptr || !IsValid(GameStateBase)) return;
	if (ATMMAGameStateBase* CastedGameStateBase = Cast<ATMMAGameStateBase>(GameStateBase)) {
		MainGameState = CastedGameStateBase;
		MainGameState->SetP1PlayerState();
	}
	// ウィジェット
	// TODO:: いずれはプレイヤーコントローラの方に生成処理を移したい
	SetWidgetBySubclass();
	MainGameWidget->AddToViewport();
	// プレイヤー
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr || !IsValid(PlayerPawn)) return;
	if (ATMMAPlayerBase* CastedPlayerPawn = Cast<ATMMAPlayerBase>(PlayerPawn)) {
		ControllPlayer = CastedPlayerPawn;
	}
	// コントローラー
	// プレイヤーステート側にて設定.
	if (!MainGameState->GetP1PlayerState()) return;
	MainGameState->GetP1PlayerState()->SetControllerByCast();
	ATMMAPlayerController* MainPlayerController = MainGameState->GetP1PlayerState()->GetMainPlayerController();
	if (!MainPlayerController) return;
	MainPlayerController->SetControllPawn(ControllPlayer);
	// ウィジェット
	MainPlayerController->CreateMainGameWidget();
	// カメラ設定
	SetPlayerCamerBySoftClass();
	IsClear = false;
	SetGoalBossLockCollisionByClass();
	// 落下後のスタート地点候補設定
	SetZkillStartPointArray();
	// 次のレベルをあらかじめ読み込んでおく.
	LoadNextLevel();
	// ステージ開始時の設定
	InitializeStage(CustomWorldSettings->CurrentStage);
	// ステージBGM再生
	SpawnAndPlayStageBGM(0);
	// ウィジェット操作用ポーン生成
	SpawnWidgetControllPawnBySoftClass();
}

void ATestMyMakeActionGameModeBase::InitializeStage(ECurrentStageEnum InCurrentStageEnum)
{
	MainGameState->SetMainGameInstance(MainGameInstance);
	MainGameState->TakeOverStatusToStage(ControllPlayer, InCurrentStageEnum);
}

void ATestMyMakeActionGameModeBase::SetWidgetBySubclass() 
{
	TSubclassOf<UTMMAMaingameWidgetBase> MainGameWidgetclass = MainGameWidgetSoftClass.LoadSynchronous();
	MainGameWidget = CreateWidget<UTMMAMaingameWidgetBase>(GetWorld(), MainGameWidgetclass);
	TSubclassOf<UContinueWidget> ContinueWidgetClass = ContinueWidgetSoftClass.LoadSynchronous();
	ContinueWidget = CreateWidget<UContinueWidget>(GetWorld(), ContinueWidgetClass);
	TSubclassOf<UTMMAGameOverWidget> GameOverWidgetClass = GameOverWidgetSoftClass.LoadSynchronous();
	GameOverWidget = CreateWidget<UTMMAGameOverWidget>(GetWorld(), GameOverWidgetClass);
}

void ATestMyMakeActionGameModeBase::SetMainGameInstance(UTMMAGameInstanceBase* InGameInstance)
{
	MainGameInstance = InGameInstance;
}

void ATestMyMakeActionGameModeBase::SetMainGameState(ATMMAGameStateBase* InMainGameState)
{
	MainGameState = InMainGameState;
}

void ATestMyMakeActionGameModeBase::InitializeGameRank()
{
	GameRank = 0;
}

void ATestMyMakeActionGameModeBase::SetMainGameWidget(UTMMAMaingameWidgetBase* InMainGameWidget)
{
	MainGameWidget = InMainGameWidget;
}

void ATestMyMakeActionGameModeBase::TakeStageClear()
{
	if (MainGameState != nullptr) {
		MainGameState->TakeStageClear();
	}
	UpdateGameRank(1);
	if (IsValid(ControllPlayer) == true) {
		ControllPlayer->StageClearLifeRegain(30);
		ControllPlayer->SetIsInvinsible(true);
		if (MainGameInstance != nullptr) {
			if (MainGameState != nullptr) {
				MainGameInstance->StageClearGameStatusAndPlayerStatus(MainGameState, ControllPlayer);
			}
			if (StageBgmComponent != nullptr) {
				MainGameInstance->SetStageBgmComponent(StageBgmComponent);
			}
		}
		SetIsLockTimer(true);
		if (GetWorld()->GetMapName() != "hororetyutyuparero") {
			ExecuteOpenNextLevel();
		}
	}
	if (MainGameInstance) {
		// ボスBGM停止
		if (MainGameState->GetCurrentStage() == ECurrentStageEnum::Stage1) return; // ステージ1はシームレスに行いたいので、すっ飛ばす.
		MainGameInstance->StopBgm();
	}
}

void ATestMyMakeActionGameModeBase::LoadNextLevel()
{
	FName StageName = FName(TEXT(""));
	switch (MainGameState->GetCurrentStage()) {
		default:
			break;
		case ECurrentStageEnum::Stage1:
			StageName = FName(TEXT("stage2"));
			break;
		case ECurrentStageEnum::Stage2:
			StageName = FName(TEXT("stage3"));
			break;
		case ECurrentStageEnum::Stage3:
			StageName = FName(TEXT("stage4"));
			break;
		case ECurrentStageEnum::Stage4:
			StageName = FName(TEXT("stage5"));
			break;
		case ECurrentStageEnum::Stage5:
			StageName = FName(TEXT("stage6"));
			break;
		case ECurrentStageEnum::Stage6:
			StageName = FName(TEXT("stage7"));
			break;
		case ECurrentStageEnum::Stage7:
			StageName = FName(TEXT("AllClear"));
			break;
	}
	if (StageName != FName(TEXT(""))) {
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(GetWorld(), StageName, false, true, LatentInfo);
	}

}

void ATestMyMakeActionGameModeBase::ExecuteOpenNextLevel()
{
	float DelayTime = 5.0;
	if (MainGameState->GetCurrentStage() == ECurrentStageEnum::Stage7) {
		DelayTime = 10.0;
	}
	FTimerHandle _TimerHandle;
	GetWorldTimerManager().SetTimer(_TimerHandle, this, &ATestMyMakeActionGameModeBase::OpenNextLevel, DelayTime, false);
}

void ATestMyMakeActionGameModeBase::OpenNextLevel() 
{
	FString StageName = "";
	switch (MainGameState->GetCurrentStage()) {
		case ECurrentStageEnum::Stage1:
			StageName ="stage2";
			break;
		case ECurrentStageEnum::Stage2:
			StageName = "stage3";
			break;
		case ECurrentStageEnum::Stage3:
			StageName ="stage4";
			break;
		case ECurrentStageEnum::Stage4:
			StageName ="stage5";
			break;
		case ECurrentStageEnum::Stage5:
			StageName ="stage6";
			break;
		case ECurrentStageEnum::Stage6:
			StageName = "stage7";
			break;
		case ECurrentStageEnum::Stage7:
			StageName = "AllClear";
			break;
	}

	if (StageName != "") {
		UGameplayStatics::OpenLevel(GetWorld(), FName(StageName));
	}
}


// ミス発生イベント
void ATestMyMakeActionGameModeBase::PlayerMiss(EPlayerMissType InPlayerMissType)
{
	SetPlayerMissType(InPlayerMissType);
	MainGameInstance->MissPlayerState(ControllPlayer);
	SetRestartPointByActor();
	USoundBase* MissSound = ControllPlayer->GetDefeatMissVoice();
	switch (PlayerMissType)
	{
	case EPlayerMissType::DropOut:
		MissSound = ControllPlayer->GetDropOutMissVoice();
		break;
	default:
		break;
	}
	UGameplayStatics::PlaySound2D(GetWorld(), MissSound);
	MainGameState->SetTimeLockFlag(true);
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &ATestMyMakeActionGameModeBase::TimerMissFunc, 1.0f, false);
	}

void ATestMyMakeActionGameModeBase::TimerMissFunc()
{
	ControllPlayer->Destroy();
	RestartPlayerAndCamera();
	SequenceAfterMiss();
}

// ミス後の処理
void ATestMyMakeActionGameModeBase::SequenceAfterMiss()
{
//	MainGameState->AddPlayerLeft(-1);
	MainGameState->GetP1PlayerState()->ChangeLeft(false);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController) return; // コントローラー取得失敗時に途中で終了.
	int Left = MainGameState->GetP1PlayerState()->GetLeft();
	if (Left >= 0) {
		MainGameWidget->UpdateLeft(Left);
		MainGameState->SetStageTime(120.0);
		if (ATMMAPlayerController* CastedPlayerController = Cast<ATMMAPlayerController>(PlayerController)) {
			CastedPlayerController->SetControllPawn(ControllPlayer);
		}
	}
	else {
		MainGameInstance->Set1PScore(MainGameState->GetP1PlayerState()->GetScore());
		MainGameInstance->SavePlayerStatus();
		MainGameInstance->CheckRankIn();
		if (IsValid(ContinueWidget) == true) {
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(true);
			PlayerController->SetInputMode(FInputModeGameAndUI());
			ViewContinueScreen(PlayerController);
		}
	}
}

// コンティニュー画面へ移動
void ATestMyMakeActionGameModeBase::ViewContinueScreen(APlayerController* PlayerController)
{
	if (IsValid(WidgetControllPawn) == true) {
		ContinueWidget->AddToViewport();
		ContinueWidget->GetItemList()->SelectedButtonByRowColumn(0, 0, PlayerController);
		WidgetControllPawn->SetControllWidget(ContinueWidget);
		PlayerController->Possess(WidgetControllPawn);
		if (ATMMAPlayerController* CastedPlayerController = Cast<ATMMAPlayerController>(PlayerController)) {
			CastedPlayerController->SetControllPawn(WidgetControllPawn);
		}
	}
}

// コンティニュー処理一括
void ATestMyMakeActionGameModeBase::Continue()
{
	ControllPlayer->SetLifeSpan(0.1);
	MainGameState->SetStateContinue();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ATMMAPlayerController* CastedPlayerController = Cast<ATMMAPlayerController>(PlayerController)) {
		CastedPlayerController->UnPossess();
		RestartPlayerAndCamera(); // 操作キャラの再生成
		CastedPlayerController->SetControllPawn(ControllPlayer);
		ContinuePlayerStatus(MainGameInstance, ControllPlayer);
		CastedPlayerController->SetInputMode(FInputModeGameOnly());
	}
	ContinueWidget->RemoveFromParent();
	MainGameWidget->UpdateLeft(MainGameState->GetP1PlayerState()->GetLeft());
}

void  ATestMyMakeActionGameModeBase::ContinuePlayerStatus(UTMMAGameInstanceBase* InGameInstance, ATMMAPlayerBase* InPlayerActor)
{
	InPlayerActor->SetShotLevel(InGameInstance->GetP1PowerLevel());
	InPlayerActor->SetBurstCount(InGameInstance->GetP1LeftBurst());
	InPlayerActor->SetShotType(EShotType::Rapid);

}

void ATestMyMakeActionGameModeBase::RestartPlayerAndCamera()
{
	ATMMAPlayerBase* SpawnedPlayer;
	RespawnPlayer(SpawnedPlayer);
	if (IsValid(SpawnedPlayer)) {
		UGameplayStatics::GetPlayerController(this, 0)->Possess(SpawnedPlayer);
		SpawnedPlayer->SetInvinsible();
		FVector PlayerLocation = SpawnedPlayer->GetActorLocation();
		PlayerLocation.X -= 330.0;
		PlayerLocation.Z += 100.0;
		PlayerCamera->SetRestartCamera(PlayerLocation);
		SpawnedPlayer->SetMainGameMode(this);
		SetControllPlayer(SpawnedPlayer);
	}
	MainGameState->SetTimeLockFlag(false);
}


//　タイムアップしたらtrueを返す.
bool ATestMyMakeActionGameModeBase::UpDateStageTime(float DeltaSeconds) {
	if (IsLockTimer) {
		return false;
	}
	else {
		float LaterStageTime = LeftStageTime - (DeltaSeconds * DecreaseTimeFactor);
		if (LaterStageTime < 0) {
			//		UpdatePlayer1Left(-1); // BP上で処理としてやるかも.
			LeftStageTime = 100.0;
			return true;
		}
		else {
			LeftStageTime = LaterStageTime;
			return false;
		}
	}
}

bool ATestMyMakeActionGameModeBase::UpdateStageTimeAndText(float DeltaSeconds)
{
	if (MainGameWidget->TimeText != nullptr) {
		bool TimeOut = UpDateStageTime(DeltaSeconds);
		int TimeInt = (int)LeftStageTime;
//		MainGameWidget->TimeText->SetText(FText::FromString(FString::FromInt(LeftStageTime)));
		return TimeOut;
	} else {
		return false;
	}
}

void ATestMyMakeActionGameModeBase::SetStageTime(float InLeftStageTime)
{
	LeftStageTime = InLeftStageTime;
}


void ATestMyMakeActionGameModeBase::AddStageTime(float AddTime)
{
	LeftStageTime += AddTime;
}

void ATestMyMakeActionGameModeBase::SetIsLockTimer(bool InIsLockTimer) 
{
	IsLockTimer = InIsLockTimer;
}

void ATestMyMakeActionGameModeBase::UpdateGameRank(int AddRank)
{
	GameRank += AddRank;
}

// タイマーによるランク更新
void ATestMyMakeActionGameModeBase::TimerRank(float AddTime)
{
	RankTime += AddTime;
	if (RankTime >= 200.0) {
		RankTime = 0.0;
		UpdateGameRank(1);
	}
}

void ATestMyMakeActionGameModeBase::SetGameRank(int InRank)
{
	GameRank = InRank;
}

void ATestMyMakeActionGameModeBase::SetControllPlayer(ATMMAPlayerBase* InControllPlayer)
{
	ControllPlayer = InControllPlayer;
}

void ATestMyMakeActionGameModeBase::SetPlayerAndCamera(ATMMAPlayerBase*& SpawnedPlayer)
{
	SetIsLockTimer(false);
	RespawnPlayer(SpawnedPlayer);
	if (IsValid(SpawnedPlayer) == true) {
		SetControllPlayer(SpawnedPlayer);
		UGameplayStatics::GetPlayerController(this, 0)->Possess(SpawnedPlayer);
		SpawnedPlayer->SetInvinsible();
		if (IsValid(PlayerCamera) == true) {
			FVector PlayerLocation = SpawnedPlayer->GetActorLocation();
			PlayerLocation.X -= -330.0;
			PlayerLocation.Z += 100.0;
			PlayerCamera->SetRestartCamera(PlayerLocation);
		}
	}
}

void ATestMyMakeActionGameModeBase::RespawnPlayer(ATMMAPlayerBase*& SpawnedPlayer)
{
	TSubclassOf<ATMMAPlayerBase> SpawnPlayerClass = DummyPlayerClass;
	if (MainGameState->GetLeft() > -1) {
		switch (CurrentGameMode) {
		case ECurrentGameMode::Shooting:
			SpawnPlayerClass = ShootingPlayerClass;
			break;
		default:
			SpawnPlayerClass = ActionPlayerClass;
			break;
		}
	}
	SpawnedPlayer = GetWorld()->SpawnActor<ATMMAPlayerBase>(SpawnPlayerClass, RestartPoint);
}

void ATestMyMakeActionGameModeBase::SetPlayerCamera(ATMMAPlayerCameraBase* InPlayerCamera) {
	PlayerCamera = InPlayerCamera;
}

void ATestMyMakeActionGameModeBase::SetPlayerCamerBySoftClass()
{
	TSubclassOf<ATMMAPlayerCameraBase> PlayerCameraClass = SoftCameraClass.LoadSynchronous();
	if (PlayerCameraClass != nullptr) {
		AActor* GettedCameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), PlayerCameraClass);
		if (GettedCameraActor == nullptr || !IsValid(GettedCameraActor)) return;
		if (ATMMAPlayerCameraBase* CastedPlayerCamera = Cast<ATMMAPlayerCameraBase>(GettedCameraActor)) {
			PlayerCamera = CastedPlayerCamera;
		}
	}
}

void ATestMyMakeActionGameModeBase::SetIsBossBattle(bool InIsBossBattle)
{
	IsBossBattle = InIsBossBattle;
}

void ATestMyMakeActionGameModeBase::SetIsStageBossBattle(bool InIsStageBossBattle)
{
	IsStageBossBattle = InIsStageBossBattle;
}

void ATestMyMakeActionGameModeBase::SetPlayerMissType(EPlayerMissType InPlayerMissType)
{
	PlayerMissType = InPlayerMissType;
}

void ATestMyMakeActionGameModeBase::SetRestartPointByActor()
{
	AActor* PointActor = ControllPlayer;
	if (CurrentGameMode == ECurrentGameMode::Action) {
		if (IsBossBattle) {
			if (IsValid(BossLockColision)) {
				PointActor = BossLockColision;
				FVector BossLockColisionLocation = PointActor->GetActorLocation();
				BossLockColisionLocation.X = FIX_X_VECTOR_FOR_PLAYER;
				BossLockColisionLocation.Z += 200.0;
				FRotator PlayerRotation = ControllPlayer->GetActorRotation();
				RestartPoint = UKismetMathLibrary::MakeTransform(BossLockColisionLocation, PlayerRotation, FVector(1.0, 1.0, 1.0));
			}
		}
		else {
			switch (PlayerMissType) {
			case EPlayerMissType::Defeated:
				{
					if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(PointActor) == true) {
						FVector PointActorLocation = PointActor->GetActorLocation();
						PointActorLocation.X = FIX_X_VECTOR_FOR_PLAYER;
						//					PointActorLocation.X += 0.5;
						FRotator PointActorRotation = PointActor->GetActorRotation();
						RestartPoint = UKismetMathLibrary::MakeTransform(PointActorLocation, PointActorRotation, FVector(1.0, 1.0, 1.0));
					}
				}
				break;
			case EPlayerMissType::DropOut:
				{
					float MinDistance = 10000; //TODO::適当な値なので、自然な処理にするような形にしたい。
					for (AActor* ZkillInStartPoint : ZkillStartPointArray)
					{
						float Distance = ZkillInStartPoint->GetDistanceTo(ControllPlayer);
						if (Distance < MinDistance) {
							MinDistance = Distance;
							PointActor = ZkillInStartPoint;
						}
					}
					if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(PointActor) == true) {
						FVector PointActorLocation = PointActor->GetActorLocation();
						PointActorLocation.Z += 200;
//						PointActorLocation.X -= 10;
						PointActorLocation.X = FIX_X_VECTOR_FOR_PLAYER;
						FRotator PointActorRotation = PointActor->GetActorRotation();
						RestartPoint = UKismetMathLibrary::MakeTransform(PointActorLocation, PointActorRotation, FVector(1.0, 1.0, 1.0));
					}
				}
				break;
			}
		}

	}
	else {
		if (IsValid(BossLockColision)) {
			PointActor = BossLockColision;
			FVector BossLockColisionLocation = PointActor->GetActorLocation();
			BossLockColisionLocation.Z += 200.0;
			BossLockColisionLocation.X = FIX_X_VECTOR_FOR_PLAYER;
			FRotator PlayerRotation = ControllPlayer->GetActorRotation();
			RestartPoint = UKismetMathLibrary::MakeTransform(BossLockColisionLocation, PlayerRotation, FVector(1.0, 1.0, 1.0));
		}
	}
	UE_LOG(LogTemp, Log, TEXT("ATestMyMakeActionGameModeBase::SetRestartPointByActor() Completed"));
}

void ATestMyMakeActionGameModeBase::SetZkillStartPointArray()
{
	// サブクラスへ読み込み
	TSubclassOf<AActor> ZkillStartClass = SoftZkillStartClass.LoadSynchronous();
	if (ZkillStartClass == nullptr) return; // nullだったら何もしない.
	TArray<AActor*> GettedActorList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ZkillStartClass, GettedActorList);
	for (AActor* ZkillStartActor : GettedActorList) {
		HouseZkillStartPointArray(ZkillStartActor);
	}
}

void ATestMyMakeActionGameModeBase::HouseZkillStartPointArray(AActor* InZKillStartPoint)
{
	// TODO::その気になれば何でも入っちゃうので、制限をかける.
	ZkillStartPointArray.Add(InZKillStartPoint);
}

void ATestMyMakeActionGameModeBase::SetBossLockColision(AActor* InBossLockColition)
{
	BossLockColision = InBossLockColition;
}

void ATestMyMakeActionGameModeBase::SetCurrentStage(ECurrentStage InCurrentStage)
{
	CurrentStage = InCurrentStage;
}
void ATestMyMakeActionGameModeBase::ConvertCurrentStageToInt(int& CurrentStageInt)
{
	switch (CurrentStage)
	{
		case ECurrentStage::Stage1:
			CurrentStageInt = 1;
			break;
		case ECurrentStage::Stage2:
			CurrentStageInt = 2;
			break;
		case ECurrentStage::Stage3:
			CurrentStageInt = 3;
			break;
		case ECurrentStage::Stage4:
			CurrentStageInt = 4;
			break;
		case ECurrentStage::Stage5:
			CurrentStageInt = 5;
			break;
		case ECurrentStage::Stage6:
			CurrentStageInt = 6;
			break;
		case ECurrentStage::Stage7:
			CurrentStageInt = 7;
			break;
		default:
			CurrentStageInt = 0;
			break;
	}
}

void ATestMyMakeActionGameModeBase::SetGoalBossLockCollision(AActor* InGoalBossLockCollision)
{
	GoalBossLockCollision = InGoalBossLockCollision;
}

void ATestMyMakeActionGameModeBase::SetGoalBossLockCollisionByClass()
{
	TSubclassOf<AActor> LockCollisionClass = SoftBossLockCollision.LoadSynchronous();
	if (LockCollisionClass == nullptr) return;
	TArray<AActor*> ActorList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), LockCollisionClass, ActorList);
	if (ActorList.Num() >= 1) {
		for (int idx = 0; idx < ActorList.Num(); idx++) {
			UE_LOG(LogTemp, Log, TEXT("FindActorNum=%d"),idx);
			if (ActorList[idx]->ActorHasTag("StageBossLock") == true) {
				UE_LOG(LogTemp, Log, TEXT("Find of GoalActor."));
				GoalBossLockCollision = ActorList[idx];
				break;
			}
		}
	}
}


void ATestMyMakeActionGameModeBase::CheckPenaltyDistanceGoalToPlayer()
{
	if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(ControllPlayer) == true)
	{
		if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(GoalBossLockCollision) == true) {
			DistancePlayerAndGoal = GoalBossLockCollision->GetActorLocation().Y - ControllPlayer->GetActorLocation().Y;
			if (DistancePlayerAndGoal < MinDistancePlayerAndGoal) {
				MinDistancePlayerAndGoal = DistancePlayerAndGoal;
				PenaltyCount = 0;
			}
			else {
				if (IsBossBattle == false) {
					PenaltyCount++;
					if (PenaltyCount % 100 == 0) {
						ViewNavigation();
					}
					if (PenaltyCount > BorderPenaltyCount) {
						if (UTMMAUnrealLibrary::GetIsNotNullPtrAndIsValid(MainGameState) == true) {
							MainGameState->AddGameRank(1);
							MainGameState->AddDecreaseTimeFactor(0.5);
						}
						GameRank++;
						DecreaseTimeFactor += 0.5;
						PenaltyCount = 0;
					}
				}
			}
		}
	}
}

void ATestMyMakeActionGameModeBase::SetIsClear(bool InIsClear)
{
	IsClear = InIsClear;
}

void ATestMyMakeActionGameModeBase::SetCurrentGameMode(ECurrentGameMode InCurrentGameMode)
{
	CurrentGameMode = InCurrentGameMode;
}

// ステージBGM生成
void ATestMyMakeActionGameModeBase::SpawnAndPlayStageBGM(int InIndexOfSoundType)
{
	// ステージ1～2はシームレスに行いたいので、処理は行わない.
	if (MainGameState->GetCurrentStage() == ECurrentStageEnum::Stage2) return;
	MainGameInstance->SpawnAndSetBgm(EGameSoundType::Stage, InIndexOfSoundType); // インスタンス側で処理を行う.
}

// ボスBGM生成
void ATestMyMakeActionGameModeBase::SpawnAndPlayBossBGM(int InIndexOfSoundType) 
{
	// ステージ1はボスBGM無し
	if (MainGameState->GetCurrentStage() == ECurrentStageEnum::Stage1) return;
	MainGameInstance->FadeOutBgm();
	MainGameInstance->SpawnAndSetBgm(EGameSoundType::Boss, InIndexOfSoundType); // インスタンス側で処理を行う.
}

void ATestMyMakeActionGameModeBase::SetStageBgmComponent(UAudioComponent* InStageBgmComponent)
{
	StageBgmComponent = InStageBgmComponent;
}

void ATestMyMakeActionGameModeBase::SetNavigationDirect(ENavigationDirect InNavigationDirect) {
	NavigationDirect = InNavigationDirect;
}

void ATestMyMakeActionGameModeBase::SetIsDirectLeftSide(bool InIsDirectLeftSide)
{
	IsDirectLeftSide = InIsDirectLeftSide;
	if (MainGameWidget != nullptr && MainGameWidget->DirectionWidget != nullptr) {
		MainGameWidget->DirectionWidget->SetIsLeftSide(InIsDirectLeftSide);
	}
}

void ATestMyMakeActionGameModeBase::ViewNavigation()
{
	if (!MainGameState->GetP1PlayerState()->GetMainPlayerController()->GetMainGameWidget() || !MainGameState->GetP1PlayerState()->GetMainPlayerController()->GetMainGameWidget()->DirectionWidget) return;
	UTMMADirectionWidget* DirectionWidget = MainGameState->GetP1PlayerState()->GetMainPlayerController()->GetMainGameWidget()->DirectionWidget;
	DirectionWidget->SetVisibility(ESlateVisibility::Visible);
	DirectionWidget->SetIsView(true);
	switch (NavigationDirect)
	{
	case ENavigationDirect::Left:
		DirectionWidget->SetDirectionTypeAndText(EDirectionType::Left);
		break;
	case ENavigationDirect::Up:
		DirectionWidget->SetDirectionTypeAndText(EDirectionType::Up);
		break;

	case ENavigationDirect::Down:
		DirectionWidget->SetDirectionTypeAndText(EDirectionType::Down);
		break;
	default:
		DirectionWidget->SetDirectionTypeAndText(EDirectionType::Right);
		break;
	}
	FVector2D Translation = FVector2D(1140.0f, 140.0f);
	if (IsDirectLeftSide == true) {
		Translation = (FVector2D(200.0f, 128.0f));
	}
	MainGameState->GetP1PlayerState()->GetMainPlayerController()->GetMainGameWidget()->SetDirectionWidgetByIsLeftSide(IsDirectLeftSide);

	/*
	if (MainGameWidget != nullptr && MainGameWidget->DirectionWidget != nullptr) {
		UTMMADirectionWidget* DirectionWidget = MainGameWidget->DirectionWidget;
		DirectionWidget->SetVisibility(ESlateVisibility::Visible);
		DirectionWidget->SetIsView(true);
		switch (NavigationDirect)
		{
			case ENavigationDirect::Left :
				DirectionWidget->SetDirectionTypeAndText(EDirectionType::Left);
				break;
			case ENavigationDirect::Up :
				DirectionWidget->SetDirectionTypeAndText(EDirectionType::Up);
				break;

			case ENavigationDirect::Down :
				DirectionWidget->SetDirectionTypeAndText(EDirectionType::Down);
				break;
			default:
				DirectionWidget->SetDirectionTypeAndText(EDirectionType::Right);
				break;
		}
		FVector2D Translation = FVector2D(1140.0f, 140.0f);
		if (IsDirectLeftSide == true) {
			Translation = (FVector2D(200.0f, 128.0f));
		}
		MainGameWidget->SetDirectionWidgetByIsLeftSide(IsDirectLeftSide);

	}
	*/
}

// コンティニューウィジェット設定
void ATestMyMakeActionGameModeBase::SetContinueWidget(UContinueWidget* InContinueWidget)
{
	ContinueWidget = InContinueWidget;
}

// ソフト参照クラスからウィジェット操作用ポーンを生成
void ATestMyMakeActionGameModeBase::SpawnWidgetControllPawnBySoftClass()
{
	TSubclassOf<ATMMAWidgetControllPawn> WidgetControllPawnClass = SoftWidgetControllPawnClass.LoadSynchronous();
	if (!WidgetControllPawnClass) return; // クラス読み込み失敗は何もしない
	FTransform SpawnTransform = UKismetMathLibrary::MakeTransform(FVector(0.0, 0.0, 0.0), FRotator(0.0, 0.0, 0.0), FVector(1.0, 1.0, 1.0));
	ATMMAWidgetControllPawn* SpawnWidgetControllPawn = GetWorld()->SpawnActor<ATMMAWidgetControllPawn>(WidgetControllPawnClass, SpawnTransform);
	if (!SpawnWidgetControllPawn) return; //生成失敗は何もしない.
	WidgetControllPawn = SpawnWidgetControllPawn;
}


// コンティニューウィジェット操作用ポーン設定
void ATestMyMakeActionGameModeBase::SetWidgetControllPawn(ATMMAWidgetControllPawn* InContinueControllPawn)
{
	WidgetControllPawn = InContinueControllPawn;
}

// コンティニュー用のウィジェットと操作ポーン両方設定
void ATestMyMakeActionGameModeBase::SetContinueWidgetAndControllPawn(UContinueWidget* InContinueWidget, ATMMAWidgetControllPawn* InContinueControllPawn)
{
	SetContinueWidget(InContinueWidget);
	SetWidgetControllPawn(InContinueControllPawn);
}


//ゲームオーバー用ウィジェットの設定
void ATestMyMakeActionGameModeBase::SetGameOverWidget(UTMMAGameOverWidget* InGameOverWidget)
{
	GameOverWidget = InGameOverWidget;
}