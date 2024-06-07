// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Character/BallPlayer.h"
#include "InGameGameMode.generated.h"

/**
 *
 */
UCLASS()
class ROLLINGBALL_API AInGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor
	AInGameGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/** Playerを破棄する **/
	void KillPlayer(ABallPlayer* Player);

	/** GameをRestartする **/
	void RestartGame();

	/** 取得したコインの枚数を追加する */
	int AddCoin(const int32 CoinNumber);

	// PlayerをRespawnする位置情報
	FTransform SpawnTransform;

private:
	/** PlayerをRespawnする **/
	void RespawnPlayer();
};