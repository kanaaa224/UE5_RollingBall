// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElements/ItemHeart.h"
#include "Character/BallPlayer.h"
#include "Kismet/GameplayStatics.h"

AItemHeart::AItemHeart() {
	// StaticMeshをLoadしてStaticMeshComponentのStaticMeshに設定
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/RollingBall/Items/Meshes/S_Heart"));

	// StaticMeshをStaticMeshComponentに設定
	ItemMesh->SetStaticMesh(Mesh);
}

void AItemHeart::GetItem() {
	// BallPlayerを取得
	if (ABallPlayer* Player = Cast<ABallPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))) {
		// Playerを回復
		float Health = Player->Heal(HealValue);

		UE_LOG(LogTemp, Display, TEXT("Health:%f"), Health);
	}
}