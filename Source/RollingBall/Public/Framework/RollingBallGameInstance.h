// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RollingBallGameInstance.generated.h"

UCLASS()
class ROLLINGBALL_API URollingBallGameInstance : public UGameInstance {
	GENERATED_BODY()

public:
	// 初期化
	void Initialize();

public:
	// 取得したコインの数
	int32 TotalCoins = 0;

	// Playerの残機
	int32 TotalLifes = 3;
};