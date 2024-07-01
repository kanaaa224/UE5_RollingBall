// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Framework/RollingBallGameInstance.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ButtonPlayのOnClickedに「OnButtonPlayClicked」を関連づける
	ButtonPlay->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonPlayClicked);

	// ButtonQuitのOnClickedに「OnButtonQuitClicked」を関連づける
	ButtonQuit->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnButtonQuitClicked);
}

void UMainMenuWidget::OnButtonPlayClicked()
{
	// GameInstanceの変数を初期化する
	URollingBallGameInstance* GameInstance = Cast<URollingBallGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->Initialize();

	// Level01をLoadする
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Level01")));
}

void UMainMenuWidget::OnButtonQuitClicked()
{
	// PlayerControllerを取得する
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		// ゲームを終了する
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}