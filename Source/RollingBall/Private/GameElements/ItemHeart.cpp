// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElements/ItemHeart.h"
#include "Character/BallPlayer.h"
#include "Kismet/GameplayStatics.h"

AItemHeart::AItemHeart()
{
	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/RollingBall/Items/Meshes/S_Heart"));

	// StaticMeshをStaticMeshComponentに設定する
	ItemMesh->SetStaticMesh(Mesh);
}

void AItemHeart::GetItem()
{
	// BallPlayerを取得する
	if (ABallPlayer* Player = Cast<ABallPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		// Playerを回復する
		float Health = Player->Heal(HealValue);

		UE_LOG(LogTemp, Display, TEXT("Health:%f"), Health);
	}
}