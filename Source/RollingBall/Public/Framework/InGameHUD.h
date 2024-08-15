// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"

UCLASS()
class ROLLINGBALL_API AInGameHUD : public AHUD {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Pauseメニューの表示/非表示
	void DispPause(bool IsPause);

	// Levelを開く
	void OpenLevel(FName LevelName);

	// Gameを終了
	void QuitGame();

	// GameOverメニューを表示
	void DispGameOver();

	// Gameを再開
	void ContinueGame();

private:
	// PauseWidgetを保持する変数
	UUserWidget* PauseWidget;

	// GameOverWidgetを保持する変数
	UUserWidget* GameOverWidget;
};