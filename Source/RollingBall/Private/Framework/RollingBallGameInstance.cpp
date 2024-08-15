// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/RollingBallGameInstance.h"

void URollingBallGameInstance::Initialize() {
	// 初期値を持つ同じクラスのDefaultObjectを取得する
	const URollingBallGameInstance* DefaultObject = GetDefault<URollingBallGameInstance>();

	// 初期値を設定する
	this->TotalCoins = DefaultObject->TotalCoins;
	this->TotalLifes = DefaultObject->TotalLifes;
}