// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/InGameGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

AInGameGameMode::AInGameGameMode()
{
	DefaultPawnClass = ABallPlayer::StaticClass();
}

void AInGameGameMode::KillPlayer(ABallPlayer* Player)
{
	// Playerを破棄する
	Player->Destroy();

	// Respawnを行う
	RespawnPlayer();
}

void AInGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Viewportに配置されたPlayerStartを探す
	const APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	// PlayerStartの位置情報をRespornの位置として保持する
	SpawnTransform = PlayerStart->GetActorTransform();
}

void AInGameGameMode::RespawnPlayer()
{
	// BallPlayerをSpawnする
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ABallPlayer* Player = GetWorld()->SpawnActor<ABallPlayer>(ABallPlayer::StaticClass(), SpawnTransform, SpawnInfo);

	// Controllerを設定する
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->Possess(Player);
}