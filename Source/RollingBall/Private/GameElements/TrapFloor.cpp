// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElements/TrapFloor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Character/BallPlayer.h"

// Sets default values
ATrapFloor::ATrapFloor() {
	// StaticMeshComponentを追加し、RootComponentに設定する
	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = TrapMesh;

	// StaticMeshをLoadしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/RollingBall/Environment/Meshes/S_TrapFloor"));

	// StaticMeshをStaticMeshComponentに設定する
	TrapMesh->SetStaticMesh(Mesh);

	// BoxComponentを追加し、BoxComponentをRootComponentにAttachする
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(RootComponent);

	// Boxのサイズを設定する
	Box->SetBoxExtent(FVector(50.0f, 50.0f, 20.0f));

	// Boxの位置を調整する
	Box->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f), false);

	// OnComponentBeginOverlapをBindする
	Box->OnComponentBeginOverlap.AddDynamic(this, &ATrapFloor::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void ATrapFloor::BeginPlay() {
	Super::BeginPlay();
}

void ATrapFloor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// 接触したActorがBallPlayerか判定
	if (ABallPlayer* Player = Cast<ABallPlayer>(OtherActor)) {
		// PlayerをReboundさせる
		Player->Rebound(Rebound);

		// PlayerにDamageを与える
		float Health = Player->TakeDamagePlayer(Damage);

		UE_LOG(LogTemp, Display, TEXT("Health:%f"), Health);
	}
}