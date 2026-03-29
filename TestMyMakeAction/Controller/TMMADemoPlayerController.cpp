// Fill out your copyright notice in the Description page of Project Settings.


#include "TMMADemoPlayerController.h"
#include "TestMyMakeAction/TMMAGameInstanceBase.h"

void ATMMADemoPlayerController::CreateAtructDemoWidget()
{
	TSubclassOf<UTMMAAtructDemoWidgetBase> AtructDemoWidgetClass = SoftAtructDemoWidgetClass.LoadSynchronous();
	if (!AtructDemoWidgetClass) return;
	AtructDemoWidget = CreateWidget<UTMMAAtructDemoWidgetBase>(GetWorld(), AtructDemoWidgetClass);
	if (AtructDemoWidget) {
		AtructDemoWidget->AddToViewport();
	}
}

// ゲーム開始
void ATMMADemoPlayerController::StartGame()
{
	if (UTMMAGameInstanceBase* CastedGameInstance = Cast<UTMMAGameInstanceBase>(GetGameInstance())) {
		if (CastedGameInstance->GetCreditCount() >= 1) {
			CastedGameInstance->UseCredit();
			FLatentActionInfo LatentInfo;
			UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("stage1")), false);
		}
	}
}

// クレジット投入
void ATMMADemoPlayerController::InsertCoin()
{
	if (UTMMAGameInstanceBase* CastedGameInstance = Cast<UTMMAGameInstanceBase>(GetGameInstance())) {
		CastedGameInstance->InsertCoin();
		// 1クレジット目の投入ならば、専用レベルへ遷移.
		if (CastedGameInstance->GetCreditCount() == 1) {
			FLatentActionInfo LatentInfo;
			UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("ReadyStart")), false);
		}
	}
}

