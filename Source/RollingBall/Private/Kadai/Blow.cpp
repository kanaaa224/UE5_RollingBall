// Fill out your copyright notice in the Description page of Project Settings.

#include "Kadai/Blow.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Character/BallPlayer.h"

// Sets default values
ABlow::ABlow() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponentを追加し、RootComponentに設定する
	BlowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = BlowMesh;

	// StaticMeshをLoadしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Kadai/Meshes/SM_Blow"));

	// StaticMeshをStaticMeshComponentに設定する
	BlowMesh->SetStaticMesh(Mesh);

	// BoxComponentを追加し、BoxComponentをRootComponentにAttachする
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(RootComponent);

	// Boxのサイズを設定する
	Box->SetBoxExtent(FVector(150.0f, 150.0f, 500.0f));

	// Boxの位置を調整する
	Box->SetRelativeLocation(FVector(0.0f, 0.0f, 500.0f), false);

	// 初期時の吹き飛ばす強さ
	BlowStrength = 30.0f;
}

// Called every frame
void ABlow::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// オーバーラップを確認
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors) {
		if (ABallPlayer* Player = Cast<ABallPlayer>(OverlappingActor)) BlowPlayer(Player);
	}
}

void ABlow::BlowPlayer(AActor* Player) {
	if (Player) {
		// プレイヤーの位置とアクターの位置を取得
		FVector PlayerLocation = Player->GetActorLocation();
		FVector ActorLocation = GetActorLocation();

		// 吹き飛ばす方向を計算
		FVector LaunchDirection = (PlayerLocation - ActorLocation).GetSafeNormal();
		LaunchDirection *= BlowStrength;

		// プレイヤーのメッシュコンポーネントを取得
		if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Player->GetComponentByClass(UStaticMeshComponent::StaticClass()))) {
			// プレイヤーを吹き飛ばす
			MeshComp->AddImpulse(LaunchDirection, NAME_None, true);
		}
	}
}