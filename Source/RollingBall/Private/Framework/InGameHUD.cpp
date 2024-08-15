// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/InGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Framework/RollingBallGameInstance.h"

void AInGameHUD::BeginPlay() {
	// WidgetBlueprintのClassを取得する
	FString StatusWidgetPath = "/Game/RollingBall/UI/Blueprints/BPW_Status.BPW_Status_C";
	TSubclassOf<class UUserWidget> StatusWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*StatusWidgetPath)).LoadSynchronous();

	// WidgetBlueprintのClassを取得する
	FString PauseWidgetPath = "/Game/RollingBall/UI/Blueprints/BPW_Pause.BPW_Pause_C";
	TSubclassOf<class UUserWidget> PauseWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*PauseWidgetPath)).LoadSynchronous();

	// WidgetBlueprintのClassを取得する
	FString GameOverWidgetPath = "/Game/RollingBall/UI/Blueprints/BPW_GameOver.BPW_GameOver_C";
	TSubclassOf<class UUserWidget> GameOverWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*GameOverWidgetPath)).LoadSynchronous();

	// PlayerControllerを取得する
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// WidgetClassとPlayerControllerが取得できたか判定する
	if (IsValid(StatusWidgetClass) && IsValid(PauseWidgetClass) && IsValid(GameOverWidgetClass) && IsValid(PlayerController)) {
		// Status表示用のWidgetを作成する
		UUserWidget* StatusWidget = UWidgetBlueprintLibrary::Create(GetWorld(), StatusWidgetClass, PlayerController);

		// Viewportに追加する
		StatusWidget->AddToViewport(0);

		// Status表示用のWidgetを作成する
		PauseWidget = UWidgetBlueprintLibrary::Create(GetWorld(), PauseWidgetClass, PlayerController);

		// Pauseメニューを折りたたみ状態にする
		PauseWidget->SetVisibility(ESlateVisibility::Collapsed);

		// Viewportに追加する
		PauseWidget->AddToViewport(1);

		// ゲームオーバー用のWidgetを作成する
		GameOverWidget = UWidgetBlueprintLibrary::Create(GetWorld(), GameOverWidgetClass, PlayerController);

		// GameOverメニューを折りたたみ状態にする
		GameOverWidget->SetVisibility(ESlateVisibility::Collapsed);

		// Viewportに追加する
		GameOverWidget->AddToViewport(2);
	}
}

void AInGameHUD::DispPause(bool IsPause) {
	// PlayerControllerを取得する
	APlayerController* PlayerController = GetOwningPlayerController();

	if (IsPause) {
		// Pauseメニューを表示する
		PauseWidget->SetVisibility(ESlateVisibility::Visible);

		// UIモードに設定する
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, PauseWidget, EMouseLockMode::DoNotLock, false);

		// GameをPause状態にする
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// Mouseカーソルを表示する
		PlayerController->SetShowMouseCursor(true);
	}
	else {
		// GameのPause状態を解除する
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		// Mouseカーソルを非表示にする
		PlayerController->SetShowMouseCursor(false);

		// GameのInput状態に戻す
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController, false);

		// Pauseメニューを折りたたみ状態にする
		PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AInGameHUD::OpenLevel(FName LevelName) {
	// LevelをLoadする
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void AInGameHUD::QuitGame() {
	// ゲームを終了する
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayerController(), EQuitPreference::Quit, false);
}

void AInGameHUD::DispGameOver() {
	// GameOverWidgetを表示する
	GameOverWidget->SetVisibility(ESlateVisibility::Visible);

	// PlayerControllerを取得する
	APlayerController* PlayerController = GetOwningPlayerController();

	// UIモードに設定する
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, GameOverWidget, EMouseLockMode::DoNotLock, false);

	// GameをPause状態にする
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	// Mouseカーソルを表示する
	PlayerController->SetShowMouseCursor(true);
}

void AInGameHUD::ContinueGame() {
	// GameInstanceを取得する
	URollingBallGameInstance* GameInstance = Cast<URollingBallGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// GameInstanceの変数を初期化する
	GameInstance->Initialize();

	// 現在のLevelNameを取得する
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	// 現在のLevelを開きなおす
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}