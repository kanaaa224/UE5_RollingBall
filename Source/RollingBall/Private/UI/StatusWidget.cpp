// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StatusWidget.h"
#include "Components/TextBlock.h"
#include "Character/BallPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/RollingBallGameInstance.h"

void UStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UStatusWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	TextBlockHealth->TextDelegate.BindUFunction(this, "SetTextBlockHealth");
	TextBlockHealthMax->TextDelegate.BindUFunction(this, "SetTextBlockHealthMax");
	TextBlockTotalLifes->TextDelegate.BindUFunction(this, "SetTextBlockTotalLifes");
	TextBlockTotalCoins->TextDelegate.BindUFunction(this, "SetTextBlockTotalCoins");

	return true;
}

FText UStatusWidget::SetTextBlockHealth()
{
	// BallPlayerを取得する
	if (const ABallPlayer* Player = Cast<ABallPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		// PlayerのHealthをTextに設定する
		return FText::FromString(FString::FromInt((int)Player->GetHealth()));
	}

	return FText();
}

FText UStatusWidget::SetTextBlockHealthMax()
{
	// BallPlayerを取得する
	if (const ABallPlayer* Player = Cast<ABallPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		// PlayerのHealthをTextに設定する
		return FText::FromString(FString::FromInt((int)Player->GetHealthMax()));
	}

	return FText();
}

FText UStatusWidget::SetTextBlockTotalLifes()
{
	// GameInstanceを取得する
	if (const URollingBallGameInstance* GameInstance = Cast<URollingBallGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		// GameInstanceのTotalLifesをTextに設定する
		return FText::FromString(FString::FromInt(GameInstance->TotalLifes));
	}

	return FText();
}

FText UStatusWidget::SetTextBlockTotalCoins()
{
	// GameInstanceを取得する
	if (const URollingBallGameInstance* GameInstance = Cast<URollingBallGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		// GameInstanceのTotalCoinsをTextに設定する
		return FText::FromString(FString::FromInt(GameInstance->TotalCoins));
	}

	return FText();
}