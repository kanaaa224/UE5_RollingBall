// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElements/ItemCoin.h"
#include "Framework/InGameGameMode.h"
#include "Kismet/GameplayStatics.h"

AItemCoin::AItemCoin()
{
	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/RollingBall/Items/Meshes/S_Coin"));

	// StaticMeshをStaticMeshComponentに設定する
	ItemMesh->SetStaticMesh(Mesh);
}

void AItemCoin::GetItem()
{
	// GameModeを取得して、InGameGameModeにCastする
	if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		int32 TotalNumber = GameMode->AddCoin(Number);

		UE_LOG(LogTemp, Display, TEXT("TotalNumber: %d"), TotalNumber);
	}
}
