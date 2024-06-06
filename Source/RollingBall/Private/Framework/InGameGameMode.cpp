// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/InGameGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

AInGameGameMode::AInGameGameMode()
{
	DefaultPawnClass = ABallPlayer::StaticClass();
}

void AInGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Viewportに配置されたPlayerStartを探す
	const APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));

	// PlayerStartの位置情報をRespornの位置として保持する
	SpawnTransform = PlayerStart->GetActorTransform();
}

void AInGameGameMode::KillPlayer(ABallPlayer* Player)
{
	// Playerを破棄する
	Player->Destroy();

	// TotalLifesをDecrimentする
	TotalLifes--;

	if (0 <= TotalLifes)
	{
		// Respawnを行う
		RespawnPlayer();
	}
	else
	{
		// GameをRestartする
		UE_LOG(LogTemp, Display, TEXT("GameOver"));
		RestartGame();
	}
}

void AInGameGameMode::RestartGame()
{
	// 現在のLevelNameを取得する
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	// 現在のLevelを開きなおす
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
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