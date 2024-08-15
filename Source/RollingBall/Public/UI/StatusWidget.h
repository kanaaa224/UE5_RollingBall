// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

class UTextBlock;

UCLASS()
class ROLLINGBALL_API UStatusWidget : public UUserWidget {
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlockHealth;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlockHealthMax;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlockTotalLifes;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlockTotalCoins;

	UFUNCTION()
	FText SetTextBlockHealth();

	UFUNCTION()
	FText SetTextBlockHealthMax();

	UFUNCTION()
	FText SetTextBlockTotalLifes();

	UFUNCTION()
	FText SetTextBlockTotalCoins();
};